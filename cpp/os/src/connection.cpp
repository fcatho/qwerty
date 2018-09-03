#include <connection.hpp>
#include <boost/bind.hpp>
#include <fstream>


Connection::Connection(Service& service)
    : m_socket(service.get())
{
}

Connection::~Connection()
{
}

void Connection::asyncRead(std::string& data)
{
    boost::asio::async_read(m_socket,
                            boost::asio::buffer(data),
                            boost::bind(&Connection::handleRead,
                                        this,
                                        data,
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

void Connection::handleRead(std::string& data,
                             const boost::system::error_code& /*error*/,
                             std::size_t bytesTransferred)
{
    if (bytesTransferred > 0)
    {
        //holder->readBuffer.vinsert(bytesTransferred);
        m_readCallback(m_address, data);
    }
}

void Connection::updateAddress()
{
    boost::asio::ip::tcp::endpoint remote, local;
    boost::system::error_code e;

    remote = m_socket.remote_endpoint(e);
    if (!e)
    {
        local = m_socket.local_endpoint(e);
    }

    if (e)
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
