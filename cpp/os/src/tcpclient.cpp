#include <tcpclient.hpp>

TcpClient(Service& service)
    : m_service(service)
    , m_acceptor(m_service.get())
{
}

TcpClient::~TcpClient()
{
}

void TcpClient::handleConnect(ConnectionPtr session, const std::string &host, uint16_t port,
                              const boost::system::error_code &error)
{
    if (error)
    {
        return;
    }

    connection->updateAddress();
    //session->start();
}
