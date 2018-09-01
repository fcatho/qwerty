#include <tcpserver.hpp>
#include <stdint.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <boost/bind.hpp>

Service::Service()
    : m_work(m_ioService)
{
}


Service::~Service()
{
    stop();
}

bool Service::start()
{
    if (m_thread.get()) {
        return false;
    }

    m_thread.reset(new boost::thread(boost::bind(&Service::run, this)));

    return true;
}

void Service::run()
{
    m_ioService.run();
}

bool Service::stop()
{
    if (!m_thread.get())
    {
        return false;
    }

    m_ioService.stop();
    m_thread->join();

    return true;
}

boost::asio::io_service& Service::get()
{
    return m_ioService;
}




Session::Session(Service& service)
    : m_socket(service.get())
{
}

Session::~Session()
{
}

void Session::asyncWrite(std::string& data)
{
    boost::asio::async_write(m_socket,
                             boost::asio::buffer(data),
                             boost::bind(&Session::handleWrite,
                                         this,
                                         data,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

boost::asio::ip::tcp::socket& Session::getSocket()
{
    return m_socket;
}

void Session::handleWrite(std::string& data,
                          const boost::system::error_code& /*error*/,
                          size_t bytes_transferred)
{
    data.erase(0, bytes_transferred);
}

void Session::updateAddress()
{
    boost::asio::ip::tcp::endpoint remote, local;
    boost::system::error_code e;

    remote = m_socket.remote_endpoint(e);
    if (!e)
    {
        local = m_socket.local_endpoint(e);
    }

    if (e)
    {
        return;
    }

    std::ostringstream stream;
    stream << "tcp://" << remote.address().to_string()
        << ":" << remote.port()
        << ":" << local.address().to_string()
        << ":" << local.port();

    m_address = stream.str();
}

const std::string& Session::getAddress() const
{
    return m_address;
}


TcpServer::TcpServer(Service& service)
    : m_service(service)
    , m_acceptor(m_service.get())
{
}

TcpServer::~TcpServer()
{
    cancel();
}

bool TcpServer::asyncListen(const uint16_t port)
{
    m_endpoint.port(port);

    if (m_acceptor.is_open())
    {
        return false;
    }

    try
    {
        m_acceptor.open(m_endpoint.protocol());
        m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        m_acceptor.bind(m_endpoint);
        m_acceptor.listen();
    }
    catch (const boost::system::system_error &)
    {
        return false;
    }

    accept();
    return true;
}

void TcpServer::cancel()
{
    if (m_acceptor.is_open())
    {
        m_acceptor.cancel();
        m_acceptor.close();
    }
}

void TcpServer::handleAccept(SessionPtr session, const boost::system::error_code &error)
{
    if (error)
    {
        return;
    }

    session->updateAddress();
    add(session);

    if (m_acceptor.is_open())
    {
        accept();
        return;
    }
}

void TcpServer::accept()
{
    SessionPtr session(new Session(m_service));
    m_acceptor.async_accept(
        session->getSocket(),
        boost::bind(&TcpServer::handleAccept,
                    this,
                    session,
                    boost::asio::placeholders::error));
}

void TcpServer::add(SessionPtr session)
{
    m_sessions[session->getAddress()] = session;
    std::cout << "session: " << session->getAddress() << std::endl;
}

void TcpServer::remove(SessionPtr session)
{
    auto it = m_sessions.find(session->getAddress());
    if (it != m_sessions.end())
    {
        m_sessions.erase(it);
    }
}

bool TcpServer::asyncWrite(const std::string &address, std::string& data)
{
    if (address != "*")
    {
        auto sessionIterator = m_sessions.find(address);
        if (sessionIterator == m_sessions.end() || sessionIterator->second == NULL)
        {
            return false;
        }

        sessionIterator->second->asyncWrite(data);
        return true;
    }

    for (auto session : m_sessions)
    {
        session.second->asyncWrite(data);
    }

    return true;
}
