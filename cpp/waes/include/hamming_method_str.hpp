#ifndef HAMMING_METHOD_STR_HPP
#define HAMMING_METHOD_STR_HPP

#include <hamming_method.hpp>
#include <iostream>
#include <memory>

class
HammingMethodStr : public HammingMethod
{
public:
    HammingMethodStr();
    virtual ~HammingMethodStr();

public:
    typedef std::shared_ptr<HammingMethodStr> HammingMethodStrPtr;

protected:
    virtual uint8_t byteHammingDistance(const uint8_t a, const uint8_t b);
};

#endif //HAMMING_METHOD_STR_HPP
