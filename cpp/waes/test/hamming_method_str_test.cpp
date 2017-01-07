#include <hamming_method_str_test.hpp>
#include <hamming_method_str.hpp>

const size_t HammingMethodStrTest::LONG_STRING_LENGTH = 1000;

TEST_F(HammingMethodStrTest, Positive_EmptyInputs)
{
    HammingMethodStr::HammingMethodPtr hm;
    size_t expectedDistance;

    hm = HammingMethodStr::HammingMethodPtr(new HammingMethodStr());
    hm->setInputA("");
    hm->setInputB("");

    expectedDistance = 0;
    EXPECT_EQ(expectedDistance, hm->run());
}

TEST_F(HammingMethodStrTest, Positive_SingleCharacter)
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

TEST_F(HammingMethodStrTest, Positive_EqualString)
{
    HammingMethodStr::HammingMethodPtr hm;
    size_t expectedDistance;
    std::string inputA(HammingMethodStrTest::LONG_STRING_LENGTH, '0');
    std::string inputB(HammingMethodStrTest::LONG_STRING_LENGTH, '0');

    hm = HammingMethodStr::HammingMethodPtr(new HammingMethodStr());
    hm->setInputA(inputA);
    hm->setInputB(inputB);

    expectedDistance = 0;
    EXPECT_EQ(expectedDistance, hm->run());
}

TEST_F(HammingMethodStrTest, Positive_DifferentString)
{
    HammingMethodStr::HammingMethodPtr hm;
    size_t expectedDistance;
    std::string inputA(HammingMethodStrTest::LONG_STRING_LENGTH, '0');
    std::string inputB(HammingMethodStrTest::LONG_STRING_LENGTH, '1');

    hm = HammingMethodStr::HammingMethodPtr(new HammingMethodStr());
    hm->setInputA(inputA);
    hm->setInputB(inputB);

    expectedDistance = HammingMethodStrTest::LONG_STRING_LENGTH;
    EXPECT_EQ(expectedDistance, hm->run());
}

TEST_F(HammingMethodStrTest, Positive_ComplementString)
{
    HammingMethodStr::HammingMethodPtr hm;
    size_t expectedDistance;
    std::string inputA(HammingMethodStrTest::LONG_STRING_LENGTH/2, '0');
    std::string inputB(HammingMethodStrTest::LONG_STRING_LENGTH/2, '1');

    inputA += std::string(HammingMethodStrTest::LONG_STRING_LENGTH/2, '1');
    inputB += std::string(HammingMethodStrTest::LONG_STRING_LENGTH/2, '0');

    hm = HammingMethodStr::HammingMethodPtr(new HammingMethodStr());
    hm->setInputA(inputA);
    hm->setInputB(inputB);

    expectedDistance = 2*(HammingMethodStrTest::LONG_STRING_LENGTH/2);
    EXPECT_EQ(expectedDistance, hm->run());
}

TEST_F(HammingMethodStrTest, Positive_IntermittentString)
{
    HammingMethodStr::HammingMethodPtr hm;
    size_t expectedDistance;
    std::string inputA;
    std::string inputB;

    for (size_t i = 0; i < HammingMethodStrTest::LONG_STRING_LENGTH/2; ++i) {
        inputA += "01";
    }
    inputB = inputA.substr(1, 2*(HammingMethodStrTest::LONG_STRING_LENGTH/2) - 1);
    inputB += "0";

    hm = HammingMethodStr::HammingMethodPtr(new HammingMethodStr());
    hm->setInputA(inputA);
    hm->setInputB(inputB);

    expectedDistance = 2*(HammingMethodStrTest::LONG_STRING_LENGTH/2);
    EXPECT_EQ(expectedDistance, hm->run());
}

TEST_F(HammingMethodStrTest, Negative_DifferentLength)
{
    HammingMethodStr::HammingMethodPtr hm;
    size_t expectedDistance;
    std::string inputA(HammingMethodStrTest::LONG_STRING_LENGTH, '0');
    std::string inputB;

    hm = HammingMethodStr::HammingMethodPtr(new HammingMethodStr());
    hm->setInputA(inputA);
    hm->setInputB(inputB);

    //Set a dummy value that has not to be changed
    expectedDistance = 48;
    try {
        expectedDistance = hm->run();
    }
    catch(const IDistanceMethodException &e) {
    }

    EXPECT_EQ(expectedDistance, 48);
}
