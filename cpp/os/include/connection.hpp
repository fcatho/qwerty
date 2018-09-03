#pragma once

#include <service.hpp>
#include <functional>
#include <boost/asio.hpp>

class Connection
{
public:
    typedef std::function<void (std::string&, std::string&)> Functor;
    typedef boost::array<char, 128> Buffer;

    Connection(Service& service);
    ~Connection();

    void start();
    boost::asio::ip::tcp::socket& getSocket();
    void updateAddress();
    const std::string& getAddress() const;
    void asyncRead();//std::string& data);
    void asyncWrite(std::string& data);
    void setReadCallback(Functor& callback);

private:

    void handleWrite(std::string&, const boost::system::error_code&, size_t);
    void handleRead(Buffer buf, const boost::system::error_code&, size_t);

    boost::asio::ip::tcp::socket m_socket;
    std::string m_address;
    Functor m_readCallback;

};
typedef std::shared_ptr<Connection> ConnectionPtr;
