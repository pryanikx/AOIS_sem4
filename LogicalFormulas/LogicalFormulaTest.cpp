#include "CppUnitTest.h"
#include "../LogicalFormulas/LogicalFormula.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(LogicalFormulaTest)
    {
    public:
        TEST_METHOD(ConstructorTest)
        {
            LogicalFormula lf("a & b");
            const auto& vars = lf.getVariables();
            Assert::AreEqual(size_t(2), vars.size());
            Assert::IsTrue(vars.find('a') != vars.end());
            Assert::IsTrue(vars.find('b') != vars.end());
        }

        TEST_METHOD(IsOperatorTest)
        {
            Assert::IsTrue(LogicalFormula::isOperator('&'));
            Assert::IsTrue(LogicalFormula::isOperator('|'));
            Assert::IsTrue(LogicalFormula::isOperator('>'));
            Assert::IsTrue(LogicalFormula::isOperator('='));
            Assert::IsTrue(LogicalFormula::isOperator('!'));
            Assert::IsFalse(LogicalFormula::isOperator('a'));
        }

        TEST_METHOD(PrecedenceTest)
        {
            Assert::AreEqual(1, LogicalFormula::precedence('&'));
            Assert::AreEqual(1, LogicalFormula::precedence('|'));
            Assert::AreEqual(2, LogicalFormula::precedence('>'));
            Assert::AreEqual(2, LogicalFormula::precedence('='));
            Assert::AreEqual(3, LogicalFormula::precedence('!'));
        }

        TEST_METHOD(EvaluateOperationTest)
        {
            Assert::IsTrue(LogicalFormula::evaluateOperation('&', true, true));
            Assert::IsFalse(LogicalFormula::evaluateOperation('&', true, false));
            Assert::IsTrue(LogicalFormula::evaluateOperation('|', true, false));
            Assert::IsFalse(LogicalFormula::evaluateOperation('>', true, false));
            Assert::IsTrue(LogicalFormula::evaluateOperation('>', false, true));
            Assert::IsTrue(LogicalFormula::evaluateOperation('=', true, true));
            Assert::IsFalse(LogicalFormula::evaluateOperation('=', true, false));
            Assert::IsTrue(LogicalFormula::evaluateOperation('!', false, false));
            Assert::IsFalse(LogicalFormula::evaluateOperation('!', true, false));
        }

        TEST_METHOD(EvaluateRPNTest)
        {
            LogicalFormula lf("a & b");
            auto& vars = const_cast<unordered_map<char, bool>&>(lf.getVariables());
            vars['a'] = true;
            vars['b'] = false;
            Assert::IsFalse(lf.evaluateRPN("a b & "));

            vars['b'] = true;
            Assert::IsTrue(lf.evaluateRPN("a b & "));
        }

        TEST_METHOD(InfixToRPNTest)
        {
            LogicalFormula lf("a & b | c");
            string rpn = lf.infixToRPN("a & b | c");
            Assert::AreEqual(string("a b & c | "), rpn);
        }

        TEST_METHOD(PrintTruthTableTest)
        {
            LogicalFormula lf("a & b");
            lf.printTruthTable();
        }

        TEST_METHOD(SKNFTest)
        {
            LogicalFormula lf("a & b");
            string sknf = lf.sknf();
            Assert::AreEqual(string("a|b & !a|b & a|!b "), sknf);
        }

        TEST_METHOD(SDNFTest)
        {
            LogicalFormula lf("a & b");
            string sdnf = lf.sdnf();
            Assert::AreEqual(string("a&b "), sdnf);
        }
    };
}
