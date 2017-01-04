#ifndef HAMMING_METHOD_HPP
#define HAMMING_METHOD_HPP

#include <idistance_method.hpp>
#include <iostream>
#include <memory>

class
HammingMethod : public IDistanceMethod
{
public:
    HammingMethod();
    virtual ~HammingMethod();

    virtual bool run(const std::string& inputA, const std::string& inputB, uint32_t& result);

public:
    typedef std::shared_ptr<HammingMethod> HammingMethodPtr;
};

#endif //HAMMING_METHOD_HPP
