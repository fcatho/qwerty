#pragma once

#include <service.hpp>
#include <connection.hpp>

class TcpClient
{
public:
    TcpClient(Service& service);
    ~TcpClient();
    void asyncRead();
    void syncRead();
    bool asyncConnect(const std::string& host, const uint16_t port, Connection::Functor&);

private:
    Service& m_service;
    boost::asio::ip::tcp::acceptor m_acceptor;
    ConnectionPtr m_connection;

    void handleConnect(ConnectionPtr session, const std::string &host, uint16_t port,
                       const boost::system::error_code &error);
};
