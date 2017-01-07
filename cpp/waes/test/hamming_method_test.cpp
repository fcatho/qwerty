#include <idistance_method.hpp>
#include <hamming_method.hpp>
#include <gtest/gtest.h>

namespace
{
class
HammingMethodTest: public ::testing::Test
{

};

TEST_F(HammingMethodTest, Positive_SingleCharacter)
{
    HammingMethod::HammingMethodPtr hm;
    size_t expectedDistance;

    hm = HammingMethod::HammingMethodPtr(new HammingMethod());
    hm->setInputA("a");
    hm->setInputB("a");

    expectedDistance = 0;
    EXPECT_EQ(expectedDistance, hm->run());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}
