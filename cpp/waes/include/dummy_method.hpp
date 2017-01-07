#ifndef DUMMY_METHOD_HPP
#define DUMMY_METHOD_HPP

#include <idistance_method.hpp>
#include <iostream>
#include <memory>

class
DummyMethod : public IDistanceMethod<int>
{
public:
    DummyMethod();
    virtual ~DummyMethod();

    virtual size_t run();//const int& inputA, const int& inputB);

public:
    typedef std::shared_ptr<DummyMethod> DummyMethodPtr;

};

#endif //HAMMING_METHOD_HPP
