#pragma once

#include <service.hpp>
#include <boost/asio.hpp>

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
    std::string m_address;
};
typedef std::shared_ptr<Session> SessionPtr;
