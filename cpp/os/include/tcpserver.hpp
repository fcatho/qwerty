#pragma once

#include <session.hpp>
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
    std::map<std::string, SessionPtr> m_sessions;

private:
    void handleAccept(SessionPtr session, const boost::system::error_code &error);
    void accept();
    void add(SessionPtr session);
    void remove(SessionPtr session);
};
typedef std::shared_ptr<TcpServer> TcpServerPtr;
