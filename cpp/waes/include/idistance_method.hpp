#ifndef IDISTANCE_METHOD_HPP
#define IDISTANCE_METHOD_HPP

#include <string>
#include <cstdint>
#include <iostream>
#include <memory>

class IDistanceMethod
{
public:
    IDistanceMethod() {}
    virtual ~IDistanceMethod() {}

    virtual bool run(const std::string& inputA, const std::string& inputB, uint32_t& result) = 0;

public:
    typedef std::shared_ptr<IDistanceMethod> IDistanceMethodPtr;

};

#endif //IDISTANCE_METHOD_HPP
