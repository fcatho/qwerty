#include <dummy_method_test.hpp>
#include <dummy_method.hpp>

using namespace cpp::waes;
using namespace cpp::waes::test;

TEST_F(DummyMethodTest, Positive_EqualInputs)
{
    DummyMethod::DummyMethodPtr hm;
    size_t expectedDistance;

    hm = DummyMethod::DummyMethodPtr(new DummyMethod());
    hm->setInputA(0x600DC0DE);
    hm->setInputB(0x600DC0DE);

    expectedDistance = 0;
    EXPECT_EQ(expectedDistance, hm->run());
}

TEST_F(DummyMethodTest, Positive_DifferentInputs)
{
    DummyMethod::DummyMethodPtr hm;
    size_t expectedDistance;

    hm = DummyMethod::DummyMethodPtr(new DummyMethod());
    hm->setInputA(0x600DC0DE);
    hm->setInputB(0xBAADC0DE);

    expectedDistance = 1;
    EXPECT_EQ(expectedDistance, hm->run());
}
