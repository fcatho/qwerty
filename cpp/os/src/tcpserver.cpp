#include <tcpserver.hpp>
#include <stdint.h>
#include <cstdlib>
#include <iostream>

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
