#include <dummy_method.hpp>

DummyMethod::DummyMethod()
{
}

DummyMethod::~DummyMethod()
{
}

size_t
DummyMethod::run()
{
    if (m_inputA != m_inputB) return 1;
    return 0;
}
