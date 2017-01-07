#ifndef HAMMING_METHOD_HPP
#define HAMMING_METHOD_HPP

#include <idistance_method.hpp>
#include <iostream>
#include <memory>
#include <vector>

class
HammingMethod : public IDistanceMethod<std::string>
{
public:
    HammingMethod();
    virtual ~HammingMethod();

    virtual size_t run();//const std::string& inputA, const std::string& inputB);
    static std::string byte2str(const uint8_t byte);
    static std::string blob2str(const std::vector<uint8_t>& blob);

public:
    typedef std::shared_ptr<HammingMethod> HammingMethodPtr;

protected:
    virtual uint8_t byteHammingDistance(const uint8_t a, const uint8_t b);
};

#endif //HAMMING_METHOD_HPP
