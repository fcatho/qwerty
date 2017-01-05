#include <hamming_method_str.hpp>

HammingMethodStr::HammingMethodStr()
{
}

HammingMethodStr::~HammingMethodStr()
{
}

uint8_t
HammingMethodStr::byteHammingDistance(const uint8_t a, const uint8_t b)
{
    return (a != b);
}
