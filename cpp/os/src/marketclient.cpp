#include <tcpclient.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>

int main(const int argc, const char** args)
{
    if (argc != 3)
    {
        return 1;
    }

    Service service;
    TcpClient client(service);
    try
    {
        service.start();
        std::string host = std::string(args[1]);
        int port = boost::lexical_cast<int>(args[2]);
        Connection::Functor func = [] (std::string& a, std::string& d)
                {
                    std::cout << a << ": " << d << std::endl;
                };
        client.asyncConnect(host, port, func);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    while (1)
    {
        client.asyncRead();
        sleep(2);
    }
    return 0;
}
