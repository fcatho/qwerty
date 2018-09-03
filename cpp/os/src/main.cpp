#include <marketserver.hpp>
#include <iostream>

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
