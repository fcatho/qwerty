#include <marketserver.hpp>
#include <iostream>

void MarketServer::run()
{
    Service service;
    TcpServer server(service);
    try
    {
        service.start();
        server.asyncListen(1234);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    size_t i = 0;
    std::string data;
    while (1)
    {
        data = std::to_string(i++);
        server.asyncWrite("*", data);
        sleep(2);
    }
}


