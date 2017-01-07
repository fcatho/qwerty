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
HammingMethod::run()
{
    size_t result;

    //If inputs are not equal size, throw exception
    if (m_inputA.size() != m_inputB.size()) {
        throw IDistanceMethodException(m_inputA.size(), m_inputB.size());
    }

    result = 0;
    for (size_t i = 0; i < m_inputA.size(); ++i) {
        result += byteHammingDistance(static_cast<uint8_t>(m_inputA[i]), static_cast<uint8_t>(m_inputB[i]));
    }

    return result;
}

std::string
HammingMethod::byte2str(const uint8_t byte)
{
    char c = static_cast<char>(byte);
    std::string s(&c);
    return s;
}

std::string
HammingMethod::blob2str(const std::vector<uint8_t>& blob)
{
    std::string s(blob.begin(), blob.end());
    return s;
}
