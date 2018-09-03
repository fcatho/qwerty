#include <session.hpp>
#include <boost/bind.hpp>
#include <fstream>


Session::Session(Service& service)
    : m_socket(service.get())
{
}

Session::~Session()
{
}

void Session::asyncWrite(std::string& data)
{
    boost::asio::async_write(m_socket,
                             boost::asio::buffer(data),
                             boost::bind(&Session::handleWrite,
                                         this,
                                         data,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

boost::asio::ip::tcp::socket& Session::getSocket()
{
    return m_socket;
}

void Session::handleWrite(std::string& data,
                          const boost::system::error_code& /*error*/,
                          size_t bytes_transferred)
{
    data.erase(0, bytes_transferred);
}

void Session::updateAddress()
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

const std::string& Session::getAddress() const
{
    return m_address;
}
