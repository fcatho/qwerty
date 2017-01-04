#include <hamming_method.hpp>
#include <numeric>    //inner_product
#include <functional> //plus, equal_to, not2

HammingMethod::HammingMethod()
{
}

HammingMethod::~HammingMethod()
{
}

bool
HammingMethod::run(const std::string& inputA, const std::string& inputB, uint32_t& result)
{
    if (inputA.size() != inputB.size()) {
        return false;
    }

    result =  std::inner_product(
            inputA.begin(), inputA.end(), inputB.begin(),
            0, std::plus<unsigned int>(),
            std::not2(std::equal_to<std::string::value_type>())
            );

    return true;
}
