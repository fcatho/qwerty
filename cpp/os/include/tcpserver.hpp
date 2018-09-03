#pragma once

#include <connection.hpp>
#include <service.hpp>
#include <boost/function.hpp>
#include <memory>

class TcpServer
{
public:
    TcpServer(Service& service);
    ~TcpServer();

    void cancel();
    bool asyncListen(const uint16_t port);
    bool asyncWrite(const std::string &address, std::string& data);

private:
    Service& m_service;
    boost::asio::ip::tcp::acceptor m_acceptor;
    boost::asio::ip::tcp::endpoint m_endpoint;
    std::map<std::string, ConnectionPtr> m_connections;

private:
    void handleAccept(ConnectionPtr connection, const boost::system::error_code &error);
    void accept();
    void add(ConnectionPtr connection);
    void remove(ConnectionPtr connection);
};
typedef std::shared_ptr<TcpServer> TcpServerPtr;
