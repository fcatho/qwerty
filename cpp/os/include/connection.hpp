#pragma once

#include <service.hpp>
#include <boost/asio.hpp>

class Connection
{
public:
    Connection(Service& service);
    ~Connection();
    void start();
    boost::asio::ip::tcp::socket& getSocket();
    void updateAddress();
    const std::string& getAddress() const;
    void asyncRead(std::string& data);
    void asyncWrite(std::string& data);

    template<typename Functor>
    void setReadCallback(Functor callback)
    {
        m_readCallback = callback;
    }

    typedef boost::function<void (std::string&)> DataHandlerFn;
private:

    void handleWrite(std::string&, const boost::system::error_code&, size_t);
    void handleRead(std::string&, const boost::system::error_code&, size_t);

    boost::asio::ip::tcp::socket m_socket;
    std::string m_address;
    DataHandlerFn m_readCallback;

};
typedef std::shared_ptr<Connection> ConnectionPtr;
