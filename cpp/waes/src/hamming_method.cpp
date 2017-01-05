#include <hamming_method.hpp>

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

size_t
HammingMethod::run(const std::string& inputA, const std::string& inputB)
{
    size_t result;

    if (inputA.size() != inputB.size()) {
        throw IDistanceMethodException(inputA.size(), inputB.size());
    }

    result = 0;
    for (size_t i = 0; i < inputA.size(); ++i) {
        result += byteHammingDistance(static_cast<uint8_t>(inputA[i]), static_cast<uint8_t>(inputB[i]));
    }

    return result;
}
