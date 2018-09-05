#include <tcpclient.hpp>
#include <cparecord.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include<boost/program_options.hpp>

void run(const int port, const std::string& host)
{
    Service service;
    TcpClient client(service);

    service.start();
    Connection::Functor func = [] (std::string& a, std::string& d)
            {
                CpaRecord cpa;
                cpa.unpack(d);
                if (cpa.unpack(d))
                {
                    std::cout << a << ": ";
                    cpa.print();
                }
            };
    client.asyncConnect(host, port, func);

    while (1)
    {
        client.asyncRead();
        usleep(1000);
    }
}

bool parseArguments(
        int argc,
        char* argv[],
        int& port,
        std::string& host)
{
    namespace po = boost::program_options;

    po::options_description desc("marketserver options");
    desc.add_options()
    ("help", "print this message")
    ("port", po::value<int>(), "tcp port value")
    ("host", po::value<std::string>(), "host address");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.empty() || vm.count("help"))
    {
        std::cout << desc << std::endl;
        return false;;
    }

    try
    {
        port = vm["port"].as<int>();
        host = vm["host"].as<std::string>();
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
    std::string host;

    try
    {
        if (parseArguments(argc, argv, port, host))
        {
            run(port, host);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
