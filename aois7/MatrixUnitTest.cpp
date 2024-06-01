#include "CppUnitTest.h"
#include "../aois7/Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestMatrix
{
    TEST_CLASS(UnitTestMatrix)
    {
    public:

        TEST_METHOD(TestConstructor)
        {
            Matrix matrix;
            int zeroCount = 0;
            int oneCount = 0;
            for (int i = 0; i < 16; ++i) {
                for (int j = 0; j < 16; ++j) {
                    int value = matrix.getValue(i, j);
                    Assert::IsTrue(value == 0 || value == 1);
                    if (value == 0) ++zeroCount;
                    else ++oneCount;
                }
            }
            Assert::IsTrue(zeroCount > 0 && oneCount > 0);
        }

        TEST_METHOD(TestFindColumn)
        {
            Matrix matrix;
            std::vector<int> column = matrix.findColumn(0);
            Assert::AreEqual(16, (int)column.size());
        }

        TEST_METHOD(TestSetWord)
        {
            Matrix matrix;
            std::vector<int> newWord = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };
            matrix.setWord(0, newWord);
            std::vector<int> column = matrix.findColumn(0);
            Assert::IsTrue(newWord == column);
        }

        TEST_METHOD(TestSumma)
        {
            Matrix matrix;
            std::vector<int> key = { 1, 0, 1 };
            std::vector<int> result = matrix.summa(key);
            Assert::AreEqual(16, (int)result.size());
        }

        TEST_METHOD(TestF0)
        {
            Matrix matrix;
            matrix.f0(0);
            std::vector<int> column = matrix.findColumn(0);
            for (int val : column) {
                Assert::AreEqual(0, val);
            }
        }

        TEST_METHOD(TestF5)
        {
            Matrix matrix;
            std::vector<int> col1 = matrix.findColumn(0);
            matrix.f5(1, 0);
            std::vector<int> col2 = matrix.findColumn(1);
            Assert::IsTrue(col1 == col2);
        }

        TEST_METHOD(TestF10)
        {
            Matrix matrix;
            std::vector<int> col1 = matrix.findColumn(0);
            matrix.f10(1, 0);
            std::vector<int> col2 = matrix.findColumn(1);
            for (size_t i = 0; i < col1.size(); ++i) {
                Assert::AreEqual(col1[i] == 0 ? 1 : 0, col2[i]);
            }
        }

        TEST_METHOD(TestF15)
        {
            Matrix matrix;
            matrix.f15(0);
            std::vector<int> column = matrix.findColumn(0);
            for (int val : column) {
                Assert::AreEqual(1, val);
            }
        }

        TEST_METHOD(TestFindSame)
        {
            Matrix matrix;
            std::vector<std::optional<bool>> key(16, std::nullopt);
            std::vector<int> result = matrix.findSame(key);
            Assert::AreEqual(16, (int)result.size());
        }
    };
}
