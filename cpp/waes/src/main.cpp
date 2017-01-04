#include <iostream>
#include <idistance_method.hpp>
#include <hamming_method.hpp>

using namespace std;

void
usage()
{
    std::cout << "waes. Compute hamming difference between two given strings" << std::endl;
    std::cout << "Usage: " << std::endl;
    std::cout << "waes <input string A> <input string B>" << std::endl;
}

int
main(const int argc, const char** argv)
{
    if (argc != 3) {
        usage();
        return 1;
    }

    uint32_t result;
    std::string inputA;
    std::string inputB;

    inputA = std::string(argv[1]);
    inputB = std::string(argv[2]);

    IDistanceMethod::IDistanceMethodPtr idm;
    HammingMethod::HammingMethodPtr hm;
    hm = HammingMethod::HammingMethodPtr(new HammingMethod());
    idm = std::static_pointer_cast<IDistanceMethod>(hm);
    if (!idm->run(inputA, inputB, result)) {
        return 2;
    }

    std::cout << result << std::endl;

    return 0;
}
