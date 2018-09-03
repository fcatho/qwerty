#pragma once

#include <service.hpp>

class TcpClient
{
public:
    TcpClient(Service& service);
    ~TcpClient();

    template<typename Functor>
    bool TcpClient::asyncConnect(const std::string& host, const uint16_t port, Functor callback)
    {
        m_service.start();
        boost::system::error_code error;

        boost::asio::ip::tcp::resolver resolver(m_service.get());
        boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), host,
                                                    std::to_string(port));
        auto iterator = resolver.resolve(query, error);

        if (error) return false;

        ConnectionPtr connection = ConnectionPtr(new Connection(service.get()));
        connection->setReadCallback(callback);

        m_connection->socket().async_connect(*iterator,
                                             boost::bind(&TcpClient::handleConnect, this, m_connection,
                                                         host, port, boost::asio::placeholders::error));
        return true;
    }

private:
    Service& m_service;
    boost::asio::ip::tcp::acceptor m_acceptor;
};
