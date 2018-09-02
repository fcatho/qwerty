#pragma once

#include <tcpserver.hpp>

class MarketServer
{
public:
    MarketServer(const std::string& instrument,
                 const std::string& cpaFile,
                 const std::string& vdaFile);
    ~MarketServer();
    void run();

private:
    std::string m_instrument;
    std::string m_cpaFile;
    std::string m_vdaFile;
};
