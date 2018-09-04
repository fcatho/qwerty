#include <connection.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <fstream>
#include <iostream>


Connection::Connection(Service& service)
    : m_socket(service.get())
{
}

Connection::~Connection()
{
}

void Connection::asyncRead()
{
    Buffer buf;
    m_socket.async_read_some(boost::asio::buffer(buf),
                              boost::bind(&Connection::handleRead,
                                          this,
                                          buf,
                                          boost::asio::placeholders::error,
                                          boost::asio::placeholders::bytes_transferred));
}

void Connection::asyncWrite(std::string& data)
{
    boost::asio::async_write(m_socket,
                             boost::asio::buffer(data),
                             boost::bind(&Connection::handleWrite,
                                         this,
                                         data,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

boost::asio::ip::tcp::socket& Connection::getSocket()
{
    return m_socket;
}

void Connection::handleWrite(std::string& data,
                          const boost::system::error_code& /*error*/,
                          size_t bytes_transferred)
{
    data.erase(0, bytes_transferred);
}

void Connection::handleRead(Buffer buf,
                            const boost::system::error_code& error,
                            std::size_t bytesTransferred)
{
    if (error == boost::asio::error::eof)
    {
        return;
    }
    else if (error)
    {
        throw boost::system::system_error(error);
    }

    if (bytesTransferred == 0)
    {
        return;
    }

    m_message += std::string(buf.begin(), bytesTransferred);
    std::size_t end = m_message.find("@");
    std::size_t begin = m_message.find("#");


    if (begin != std::string::npos && end != std::string::npos && end < begin)
    {
        m_message.erase(0, end);
    }

    if (begin != std::string::npos && end != std::string::npos && begin < end)
    {
        std::string str = m_message.substr(begin, end - begin);
        m_readCallback(m_address, str);
        m_message.erase(begin, end);
    }
}

void Connection::updateAddress()
{
    boost::asio::ip::tcp::endpoint remote, local;
    boost::system::error_code error;

    remote = m_socket.remote_endpoint(error);
    if (!error)
    {
        local = m_socket.local_endpoint(error);
    }

    if (error)
    {
        return;
    }

    std::ostringstream stream;
    stream << "tcp://" << remote.address().to_string()
        << ":" << remote.port()
        << ":" << local.address().to_string()
        << ":" << local.port();

    m_address = stream.str();
}

const std::string& Connection::getAddress() const
{
    return m_address;
}

void Connection::setReadCallback(Functor& callback)
{
    m_readCallback = callback;
}


