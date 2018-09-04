#include <tcpclient.hpp>
#include <iostream>
#include <boost/array.hpp>

TcpClient::TcpClient(Service& service)
    : m_service(service)
    , m_acceptor(m_service.get())
{
}

TcpClient::~TcpClient()
{
}

void TcpClient::handleConnect(ConnectionPtr connection,
                              const std::string& /*host*/,
                              uint16_t /*port*/,
                              const boost::system::error_code &error)
{
    if (error)
    {
        return;
    }

    connection->updateAddress();
}

bool TcpClient::asyncConnect(const std::string& host,
                             const uint16_t port,
                             Connection::Functor& callback)
{
    m_service.start();
    boost::system::error_code error;

    boost::asio::ip::tcp::resolver resolver(m_service.get());
    boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), host,
                                                std::to_string(port));
    auto iterator = resolver.resolve(query, error);

    if (error) return false;

    m_connection = ConnectionPtr(new Connection(m_service));
    m_connection->setReadCallback(callback);

    m_connection->getSocket().async_connect(*iterator,
                                         boost::bind(&TcpClient::handleConnect, this, m_connection,
                                                     host, port, boost::asio::placeholders::error));
    return true;
}

void TcpClient::syncRead()
{
    Connection::Buffer buf;
    boost::system::error_code error;
    size_t len = m_connection->getSocket().read_some(boost::asio::buffer(buf), error);

    if (error == boost::asio::error::eof)
    {
        return;
    }
    else if (error)
    {
        throw boost::system::system_error(error);
    }

    std::string s(buf.data(), len);
    std::cout << "s.size: " << s.size() << " buf: " << s << std::endl;
}

void TcpClient::asyncRead()
{
    m_connection->asyncRead();
}
