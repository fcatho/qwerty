#include <hamming_method_test.hpp>
#include <hamming_method.hpp>

const size_t HammingMethodTest::LONG_BLOB_LENGTH = 0xFFFFFF;

TEST_F(HammingMethodTest, Positive_EmptyInputs)
{
    HammingMethod::HammingMethodPtr hm;
    size_t expectedDistance;

    hm = HammingMethod::HammingMethodPtr(new HammingMethod());
    hm->setInputA("");
    hm->setInputB("");

    expectedDistance = 0;
    EXPECT_EQ(expectedDistance, hm->run());
}

TEST_F(HammingMethodTest, Positive_SingleByte)
{
    HammingMethod::HammingMethodPtr hm;
    size_t expectedDistance;
    uint8_t inputA;
    uint8_t inputB;

    inputA = 0xFF;
    inputB = 0xFF;
    hm = HammingMethod::HammingMethodPtr(new HammingMethod());
    hm->setInputA(HammingMethod::byte2str(inputA));
    hm->setInputB(HammingMethod::byte2str(inputB));

    expectedDistance = 0;
    EXPECT_EQ(expectedDistance, hm->run());
}

TEST_F(HammingMethodTest, Positive_EqualString)
{
    HammingMethod::HammingMethodPtr hm;
    size_t expectedDistance;
    std::vector<uint8_t> inputA;
    std::vector<uint8_t> inputB;

    for (size_t i = 0; i < HammingMethodTest::LONG_BLOB_LENGTH; ++i) {
        inputA.push_back(i & 0xFF);
        inputB.push_back(i & 0xFF);
    }

    hm = HammingMethod::HammingMethodPtr(new HammingMethod());
    hm->setInputA(HammingMethod::blob2str(inputA));
    hm->setInputB(HammingMethod::blob2str(inputB));

    expectedDistance = 0;
    EXPECT_EQ(expectedDistance, hm->run());
}

TEST_F(HammingMethodTest, Positive_DifferentString)
{
    HammingMethod::HammingMethodPtr hm;
    size_t expectedDistance;
    std::vector<uint8_t> inputA;
    std::vector<uint8_t> inputB;

    for (size_t i = 0; i < HammingMethodTest::LONG_BLOB_LENGTH; ++i) {
        inputA.push_back(0x55);
        inputB.push_back(0xAA);
    }

    hm = HammingMethod::HammingMethodPtr(new HammingMethod());
    hm->setInputA(HammingMethod::blob2str(inputA));
    hm->setInputB(HammingMethod::blob2str(inputB));

    expectedDistance = HammingMethodTest::LONG_BLOB_LENGTH * 8;
    EXPECT_EQ(expectedDistance, hm->run());
}

TEST_F(HammingMethodTest, Negative_DifferentLength)
{
    HammingMethod::HammingMethodPtr hm;
    size_t expectedDistance;
    std::vector<uint8_t> inputA(HammingMethodTest::LONG_BLOB_LENGTH, 0xFF);
    std::vector<uint8_t> inputB;

    hm = HammingMethod::HammingMethodPtr(new HammingMethod());
    hm->setInputA(HammingMethod::blob2str(inputA));
    hm->setInputB(HammingMethod::blob2str(inputB));

    //Set a dummy value that has not to be changed
    expectedDistance = 48;
    try {
        expectedDistance = hm->run();
    }
    catch(const IDistanceMethodException &e) {
    }

    EXPECT_EQ(expectedDistance, 48);
}
