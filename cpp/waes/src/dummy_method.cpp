#include <dummy_method.hpp>

DummyMethod::DummyMethod()
{
}

DummyMethod::~DummyMethod()
{
}

size_t
DummyMethod::run()//const int& inputA, const int& inputB)
{

    if (m_inputA != m_inputB) return 1;
    return 0;
}
