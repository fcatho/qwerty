#include <iostream>
#include <idistance_method.hpp>
#include <hamming_method_str.hpp>

using namespace cpp::waes;

void
usage()
{
    std::cout << "hammingstr. Compute hamming difference between two given " << std::endl;
    std::cout << "            same size strings. See README.md for more details" << std::endl;
    std::cout << "Usage: " << std::endl;
    std::cout << "hammingstr <input string A> <input string B>" << std::endl;
}

int
main(const int argc, const char** argv)
{
    if (argc < 3) {
        usage();
        return 1;
    }

    uint32_t result;
    std::string inputA;
    std::string inputB;

    inputA = std::string(argv[1]);
    inputB = std::string(argv[2]);

    IDistanceMethod<std::string>::IDistanceMethodPtr idm;
    HammingMethodStr::HammingMethodStrPtr hm;

    hm = HammingMethodStr::HammingMethodStrPtr(new HammingMethodStr());
    idm = std::static_pointer_cast<IDistanceMethod<std::string> >(hm);
    idm->setInputA(inputA);
    idm->setInputB(inputB);
    try {
        result = idm->run();
        std::cout << result << std::endl;
    }
    catch(const IDistanceMethodException &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
