#include <idistance_method.hpp>
#include <hamming_method_str.hpp>
#include <gtest/gtest.h>

namespace
{
class
HammingMethodTest: public ::testing::Test
{
public:
    static const size_t LONG_STRING_LENGTH;

};

const size_t HammingMethodTest::LONG_STRING_LENGTH = 1000;

TEST_F(HammingMethodTest, Positive_EmptyInputs)
{
    HammingMethodStr::HammingMethodPtr hm;
    size_t expectedDistance;

    hm = HammingMethodStr::HammingMethodPtr(new HammingMethodStr());
    hm->setInputA("");
    hm->setInputB("");

    expectedDistance = 0;
    EXPECT_EQ(expectedDistance, hm->run());
}

TEST_F(HammingMethodTest, Positive_SingleCharacter)
{
    HammingMethodStr::HammingMethodPtr hm;
    size_t expectedDistance;

    hm = HammingMethodStr::HammingMethodPtr(new HammingMethodStr());
    hm->setInputA("0");
    hm->setInputB("0");

    expectedDistance = 0;
    EXPECT_EQ(expectedDistance, hm->run());

    hm->setInputA("0");
    hm->setInputB("1");

    expectedDistance = 1;
    EXPECT_EQ(expectedDistance, hm->run());
}

TEST_F(HammingMethodTest, Positive_EqualString)
{
    HammingMethodStr::HammingMethodPtr hm;
    size_t expectedDistance;
    std::string inputA(HammingMethodTest::LONG_STRING_LENGTH, '0');
    std::string inputB(HammingMethodTest::LONG_STRING_LENGTH, '0');

    hm = HammingMethodStr::HammingMethodPtr(new HammingMethodStr());
    hm->setInputA(inputA);
    hm->setInputB(inputB);

    expectedDistance = 0;
    EXPECT_EQ(expectedDistance, hm->run());
}

TEST_F(HammingMethodTest, Positive_DifferentString)
{
    HammingMethodStr::HammingMethodPtr hm;
    size_t expectedDistance;
    std::string inputA(HammingMethodTest::LONG_STRING_LENGTH, '0');
    std::string inputB(HammingMethodTest::LONG_STRING_LENGTH, '1');

    hm = HammingMethodStr::HammingMethodPtr(new HammingMethodStr());
    hm->setInputA(inputA);
    hm->setInputB(inputB);

    expectedDistance = HammingMethodTest::LONG_STRING_LENGTH;
    EXPECT_EQ(expectedDistance, hm->run());
}

TEST_F(HammingMethodTest, Positive_ComplementString)
{
    HammingMethodStr::HammingMethodPtr hm;
    size_t expectedDistance;
    std::string inputA(HammingMethodTest::LONG_STRING_LENGTH/2, '0');
    std::string inputB(HammingMethodTest::LONG_STRING_LENGTH/2, '1');

    inputA += std::string(HammingMethodTest::LONG_STRING_LENGTH/2, '1');
    inputB += std::string(HammingMethodTest::LONG_STRING_LENGTH/2, '0');

    hm = HammingMethodStr::HammingMethodPtr(new HammingMethodStr());
    hm->setInputA(inputA);
    hm->setInputB(inputB);

    expectedDistance = 2*(HammingMethodTest::LONG_STRING_LENGTH/2);
    EXPECT_EQ(expectedDistance, hm->run());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}
