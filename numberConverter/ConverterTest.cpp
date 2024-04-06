#include "CppUnitTest.h"
#include "../numberConverter/Binary32.h"
#include "../numberConverter/BinaryNumber.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(BinaryNumberTests)
{
public:
    TEST_METHOD(TestDirectConversion_PositiveNumber)
    {
        BinaryNumber binary(10);
        std::vector<int> expectedDir = { 0, 0, 0, 0, 1, 0, 1, 0 };
        Assert::IsTrue(expectedDir == binary.getDir());
    }

    TEST_METHOD(TestDirectConversion_NegativeNumber)
    {
        BinaryNumber binary(-10);
        std::vector<int> expectedDir = { 1, 0, 0, 0, 1, 0, 1, 0 };
        Assert::IsTrue(expectedDir == binary.getDir());
    }

    TEST_METHOD(TestReverseConversion_PositiveNumber)
    {
        BinaryNumber binary(10);
        std::vector<int> expectedRev = { 0, 0, 0, 0, 1, 0, 1, 0 };
        Assert::IsTrue(expectedRev == binary.getRev());
    }

    TEST_METHOD(TestReverseConversion_NegativeNumber)
    {
        BinaryNumber binary(-10);
        std::vector<int> expectedRev = { 1, 1, 1, 1, 0, 1, 0, 1 };
        Assert::IsTrue(expectedRev == binary.getRev());
    }

    TEST_METHOD(TestMultiply_PositiveNumbers)
    {
        BinaryNumber binary1(5);
        BinaryNumber binary2(5);
        std::vector<int> expectedSum = { 0, 0, 0, 1, 1, 0, 0, 1 };
        Assert::IsTrue(expectedSum == binary1.multiply(binary2));
    }

    TEST_METHOD(TestAddition_PositiveNumbersDirect)
    {
        BinaryNumber binary1(10);
        BinaryNumber binary2(5);
        std::vector<int> expectedSum = { 0, 0, 0, 0, 1, 1, 1, 1 };
        Assert::IsTrue(expectedSum == binary1.summary_dir(binary2));
    }

    TEST_METHOD(TestAddition_NegativeNumbersReverse)
    {
        BinaryNumber binary1(-10);
        BinaryNumber binary2(-5);
        std::vector<int> expectedSum = { 1, 1, 1, 1, 0, 0, 0, 0 };
        Assert::IsTrue(expectedSum == binary1.summary_rev(binary2));
    }

    TEST_METHOD(TestAddition_NegativeNumbersAdditional)
    {
        BinaryNumber binary1(-10);
        BinaryNumber binary2(-5);
        std::vector<int> expectedSum = { 1, 1, 1, 1, 0, 0, 0, 1 };
        Assert::IsTrue(expectedSum == binary1.summary_add(binary2));
    }

    TEST_METHOD(TestDivision)
    {
        BinaryNumber binary1(10);
        BinaryNumber binary2(5);
        std::vector<int> expectedSum = { 0, 0, 0, 0, 0, 0, 1, 0 };
        Assert::IsTrue(expectedSum == binary1.divide(binary2));
    }
};

TEST_CLASS(Binary32Tests)
{
public:
    TEST_METHOD(TestSignCreating_PositiveNumber)
    {
        Binary32 binary32(5.5);
        std::vector<int> expectedSign = { 0 };
        Assert::IsTrue(expectedSign == binary32.getSign());
    }

    TEST_METHOD(TestSignCreating_NegativeNumber)
    {
        Binary32 binary32(-5.5);
        std::vector<int> expectedSign = { 1 };
        Assert::IsTrue(expectedSign == binary32.getSign());
    }

    TEST_METHOD(TestExponentCreating_PositiveNumber)
    {
        Binary32 binary32(5.5);
        std::vector<int> expectedExp = { 1, 0, 0, 0, 0, 0, 0, 1 };
        Assert::IsTrue(expectedExp == binary32.getExponent());
    }

    TEST_METHOD(TestExponentCreating_NegativeNumber)
    {
        Binary32 binary32(-5.5);
        std::vector<int> expectedExp = { 1, 0, 0, 0, 0, 0, 0, 1 };
        Assert::IsTrue(expectedExp == binary32.getExponent());
    }

    TEST_METHOD(TestMantissaCreating_PositiveNumber)
    {
        Binary32 binary32(5.5);
        std::vector<int> expectedMant = { 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        Assert::IsTrue(expectedMant == binary32.getMantissa());
    }

    TEST_METHOD(TestMantissaCreating_NegativeNumber)
    {
        Binary32 binary32(-5.5);
        std::vector<int> expectedMant = { 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        Assert::IsTrue(expectedMant == binary32.getMantissa());
    }

    TEST_METHOD(TestBinary32Creating_PositiveNumber)
    {
        Binary32 binary32(5.5);
        std::vector<int> expectedBinary32 = { 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        Assert::IsTrue(expectedBinary32 == binary32.getBinary32());
    }

    TEST_METHOD(TestBinary32Creating_NegativeNumber)
    {
        Binary32 binary32(-5.5);
        std::vector<int> expectedBinary32 = { 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        Assert::IsTrue(expectedBinary32 == binary32.getBinary32());
    }

    TEST_METHOD(TestSummary_PositiveNumbers)
    {
        Binary32 binary32_1(5.5);
        Binary32 binary32_2(3.5);
        std::vector<int> expectedSummary = { 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        Assert::IsTrue(expectedSummary == binary32_1.summary(binary32_2));
    }
};