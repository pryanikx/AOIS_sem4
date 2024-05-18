#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <cctype>
#include <stdexcept>

using namespace std;

class LogicalFormula {
public:
    LogicalFormula(const string& exp);

    static bool isOperator(char c);
    static int precedence(char op);
    static bool evaluateOperation(char op, bool a, bool b);
    bool evaluateRPN(const string& rpn);
    string infixToRPN(const string& expression);
    void printTruthTable();
    string sknf();
    string sdnf();
    const unordered_map<char, bool>& getVariables() const;

private:
    string expression;
    unordered_map<char, bool> variables;
    vector<bool> indexForm;
    vector<int> numConForm;
    vector<int> numDizForm;
};