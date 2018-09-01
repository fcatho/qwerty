#pragma once

#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <memory>

class Service
{
public:
    Service();
    ~Service();
    bool start();
    bool stop();
    boost::asio::io_service& get();

private:
    void run();
    boost::asio::io_service m_ioService;
    std::shared_ptr<boost::thread> m_thread;
    boost::asio::io_service::work m_work;
};

class Session
{
public:
    Session(Service& service);
    ~Session();
    void start();
    boost::asio::ip::tcp::socket& getSocket();
    void updateAddress();
    const std::string& getAddress() const;
    void asyncWrite(std::string& data);

private:
    void handleWrite(std::string&, const boost::system::error_code&, size_t);

    boost::asio::ip::tcp::socket m_socket;
    //std::string m_data;
    std::string m_address;
};
typedef std::shared_ptr<Session> SessionPtr;


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
