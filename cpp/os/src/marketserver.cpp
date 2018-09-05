#include <tcpserver.hpp>
#include <service.hpp>
#include <cparecord.hpp>
#include <iostream>
#include <fstream>
#include<boost/program_options.hpp>

void run(const int port,
         const std::string& cfile,
         const std::string& /*vfile*/,
         const std::string& instrument)
{
    Service service;
    TcpServer server(service);

    service.start();
    server.asyncListen(port);
    std::ifstream in(cfile);

    std::string raw;
    while (std::getline(in, raw))
    {
        CpaRecord cpa;
        if (cpa.loadDetails(raw) && (cpa.getInstrument() == instrument || instrument.empty()))
        {
            std::cout << raw << std::endl;
            std::string data = cpa.pack();
            server.asyncWrite("*", data);
            usleep(10000);
        }
    }
}

bool parseArguments(
        int argc,
        char* argv[],
        int& port,
        std::string& cfile,
        std::string& vfile,
        std::string& instrument)
{
    namespace po = boost::program_options;

    po::options_description desc("marketserver options");
    desc.add_options()
    ("help", "print this message")
    ("port", po::value<int>(), "tcp port value")
    ("vda", po::value<std::string>(), "vda file")
    ("cpa", po::value<std::string>(), "cpa file")
    ("instrument", po::value<std::string>(), "instrument name");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.empty() || vm.count("help"))
    {
        std::cout << desc << std::endl;
        return false;;
    }

    if (vm.count("instrument"))
    {
        instrument = vm["instrument"].as<std::string>();
    }

    try
    {
        port = vm["port"].as<int>();
        vfile = ""; /*vm["vda"].as<std::string>()*/
        cfile = vm["cpa"].as<std::string>();
    }
    catch (std::exception& ex)
    {
        std::cerr << "invalid parameters. Use --help to see available options." << std::endl;
        return false;
    }

    return true;
}


int main(int argc, char* argv[])
{
    int port = -1;
    std::string vfile;
    std::string cfile;
    std::string instrument;

    try
    {
        if (parseArguments(argc, argv, port, cfile, vfile, instrument))
        {
            run(port, cfile, vfile, instrument);
        }
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}
