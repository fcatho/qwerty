#include <hamming_method.hpp>
#include <numeric>    //inner_product
#include <functional> //plus, equal_to, not2

HammingMethod::HammingMethod()
{
}

HammingMethod::~HammingMethod()
{
}

uint8_t
HammingMethod::byteHammingDistance(const uint8_t a, const uint8_t b)
{
    //Nibble lookup table to reduce computation time
    static const uint8_t NIBBLE_LOOKUP [16] =
    {
        0, 1, 1, 2, 1, 2, 2, 3, 
        1, 2, 2, 3, 2, 3, 3, 4
    };

    uint8_t xorValue = a^b;

    return NIBBLE_LOOKUP[xorValue & 0x0F] + NIBBLE_LOOKUP[xorValue >> 4];
}

//uint8_t
//HammingMethod::byteHammingDistance(const std::string& a, const std::string& b)
//{
//    //Nibble lookup table to reduce computation time
//    static const uint8_t NIBBLE_LOOKUP [16] =
//    {
//        0, 1, 1, 2, 1, 2, 2, 3, 
//        1, 2, 2, 3, 2, 3, 3, 4
//    };
//
//    uint8_t xorValue = a^b;
//
//    return NIBBLE_LOOKUP[xorValue & 0x0F] + NIBBLE_LOOKUP[xorValue >> 4];
//}
//
//size_t
//HammingMethod::run(const char* inputA, const size_t sizeInputA, const char* inputB, )
//{
//    size_t distance = 0;
//
//    for (size_t i = 0; i < sizeInputA; ++i) {
//        try {
//            distance += byteHammingDistance(static_cast<uint8_t>(inputA[i]), static_cast<uint8_t>(inputB[i]));
//        }
//        catch (...) {
//        }
//    }
//
//    return distance;
//}

bool
HammingMethod::run(const std::string& inputA, const std::string& inputB, uint32_t& result)
{
    if (inputA.size() != inputB.size()) {
        //trow exception
        return false;
    }

    result = 0;
    for (size_t i = 0; i < inputA.size(); ++i) {
        result += byteHammingDistance(static_cast<uint8_t>(inputA[i]), static_cast<uint8_t>(inputB[i]));
    }

    //result =  std::inner_product(
    //        inputA.begin(), inputA.end(), inputB.begin(),
    //        0, std::plus<size_t>(),
    //        std::not2(std::equal_to<std::string::value_type>())
    //        );

    return true;
}
