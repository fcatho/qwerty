#include <service.hpp>
#include <marketserver.hpp>
#include <cparecord.hpp>
#include <iostream>
#include <fstream>

MarketServer::MarketServer(const std::string& instrument,
                           const std::string& cpaFile,
                           const std::string& vdaFile)
    : m_instrument(instrument)
    , m_cpaFile(cpaFile)
    , m_vdaFile(vdaFile)
{
}

MarketServer::~MarketServer()
{
}

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

    std::ifstream in(m_cpaFile);
    std::string raw;
    while (std::getline(in, raw))
    {
        CpaRecord cpa;
        if (cpa.loadDetails(raw))
        {
            std::string data = cpa.pack();
            std::cout << data << std::endl;
            server.asyncWrite("*", data);
            sleep(2);
        }
    }
}

int main(const int argc, const char** args)
{
    if (argc != 4)
    {
        std::cout << "Usage: " << args[0] << " <instrument> <cpa> <vda>" << std::endl;
        return 1;
    }

    MarketServer ms(args[1], args[2], args[3]);
    ms.run();

    return 0;
}
