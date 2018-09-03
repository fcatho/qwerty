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

void TcpServer::handleAccept(ConnectionPtr connection, const boost::system::error_code &error)
{
    if (error)
    {
        return;
    }

    connection->updateAddress();
    add(connection);

    if (m_acceptor.is_open())
    {
        accept();
        return;
    }
}

void TcpServer::accept()
{
    ConnectionPtr connection(new Connection(m_service));
    m_acceptor.async_accept(
        connection->getSocket(),
        boost::bind(&TcpServer::handleAccept,
                    this,
                    connection,
                    boost::asio::placeholders::error));
}

void TcpServer::add(ConnectionPtr connection)
{
    m_connections[connection->getAddress()] = connection;
    std::cout << "connection: " << connection->getAddress() << std::endl;
}

void TcpServer::remove(ConnectionPtr connection)
{
    auto it = m_connections.find(connection->getAddress());
    if (it != m_connections.end())
    {
        m_connections.erase(it);
    }
}

bool TcpServer::asyncWrite(const std::string &address, std::string& data)
{
    if (address != "*")
    {
        auto connectionIterator = m_connections.find(address);
        if (connectionIterator == m_connections.end() || connectionIterator->second == NULL)
        {
            return false;
        }

        connectionIterator->second->asyncWrite(data);
        return true;
    }

    for (auto connection : m_connections)
    {
        connection.second->asyncWrite(data);
    }

    return true;
}
