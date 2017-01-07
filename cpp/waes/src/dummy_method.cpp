#include <dummy_method.hpp>

using namespace cpp::waes;

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
