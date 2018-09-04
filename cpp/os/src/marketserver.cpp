#include <tcpserver.hpp>
#include <service.hpp>
#include <cparecord.hpp>
#include <iostream>
#include <fstream>

int main(const int argc, const char** args)
{
    if (argc != 4)
    {
        std::cout << "Usage: " << args[0] << " <instrument> <cpa> <vda>" << std::endl;
        return 1;
    }

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

    std::ifstream in(args[2]);
    std::string raw;
    while (std::getline(in, raw))
    {
        CpaRecord cpa;
        if (cpa.loadDetails(raw))
        {
            std::cout << raw << std::endl;
            std::string data = cpa.pack();
            server.asyncWrite("*", data);
            usleep(10000);
        }
    }

    return 0;
}
