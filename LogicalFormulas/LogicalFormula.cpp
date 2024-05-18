#include "LogicalFormula.h"

LogicalFormula::LogicalFormula(const string& exp) : expression(exp) {
    for (char c : expression) {
        if (isalpha(c)) {
            variables[c] = false;
        }
    }
}

bool LogicalFormula::isOperator(char c) {
    return c == '&' || c == '|' || c == '>' || c == '=' || c == '!';
}

int LogicalFormula::precedence(char op) {
    if (op == '|' || op == '&')
        return 1;
    if (op == '>' || op == '=')
        return 2;
    if (op == '!')
        return 3;
    return 0;
}

bool LogicalFormula::evaluateOperation(char op, bool a, bool b) {
    switch (op) {
    case '&':
        return a && b;
    case '|':
        return a || b;
    case '>':
        return !a || b;
    case '=':
        return a == b;
    case '!':
        return !a;
    default:
        throw invalid_argument("Invalid operator");
    }
}

bool LogicalFormula::evaluateRPN(const string& rpn) {
    vector<bool> values;
    for (char c : rpn) {
        if (c == ' ')
            continue;
        if (isalnum(c)) {
            values.push_back(variables.at(c));
        }
        else if (isOperator(c)) {
            if (c == '!') {
                if (values.empty())
                    return false;
                bool operand = values.back();
                values.pop_back();
                values.push_back(evaluateOperation(c, operand, false));
            }
            else {
                if (values.size() < 2)
                    return false;
                bool operand2 = values.back();
                values.pop_back();
                bool operand1 = values.back();
                values.pop_back();
                bool result = evaluateOperation(c, operand1, operand2);
                values.push_back(result);
            }
        }
    }
    if (values.size() != 1)
        return false;
    return values.back();
}

string LogicalFormula::infixToRPN(const string& expression) {
    string result;
    vector<char> operators;

    unordered_map<char, int> precedence = {
        {'|', 1},
        {'&', 1},
        {'>', 2},
        {'=', 2},
        {'!', 3}
    };

    for (char c : expression) {
        if (c == ' ')
            continue;
        if (isalnum(c)) {
            result += c;
            result += ' ';
        }
        else if (c == '(') {
            operators.push_back(c);
        }
        else if (c == ')') {
            while (!operators.empty() && operators.back() != '(') {
                result += operators.back();
                result += ' ';
                operators.pop_back();
            }
            operators.pop_back();
        }
        else if (isOperator(c)) {
            while (!operators.empty() && precedence[operators.back()] >= precedence[c]) {
                result += operators.back();
                result += ' ';
                operators.pop_back();
            }
            operators.push_back(c);
        }
    }

    for (char op : operators) {
        result += op;
        result += ' ';
    }

    return result;
}

void LogicalFormula::printTruthTable() {
    cout << "\n\nTruth Table:" << endl;
    for (auto& pair : variables) {
        cout << pair.first << " ";
    }
    cout << "| Result" << endl;

    int numVars = variables.size();
    for (int i = 0; i < (1 << numVars); ++i) {
        int j = 0;
        for (auto it = std::prev(variables.end()); it != variables.begin(); --it) {
            it->second = bool((i & (1 << j)) != 0);
            j++;
        }

        variables.begin()->second = bool((i & (1 << j)) != 0);

        bool result = evaluateRPN(infixToRPN(expression));

        indexForm.push_back(result);

        for (auto& pair : variables) {
            cout << pair.second << " ";
        }
        cout << "| " << (result ? "1" : "0") << endl;
    }

    for (int i = 0; i < indexForm.size(); i++)
    {
        if (indexForm[i] == 0)
            numConForm.push_back(i);
        else
            numDizForm.push_back(i);
    }

    cout << "\n\nNumForm:\n\tConForm: ";
    for (auto el : numConForm)
    {
        cout << el;
    }

    cout << " &\n\n\tDizForm: ";
    for (auto el : numDizForm)
    {
        cout << el;
    }
    cout << " |\n\n";

    cout << "IndexForm:\n\t";
    for (auto el : indexForm)
    {
        cout << el;
    }
    cout << " - ";

    int decimal = 0;
    int power = 1;
    for (int i = indexForm.size() - 1; i >= 0; --i) {
        decimal += indexForm[i] * power;
        power *= 2;
    }
    cout << decimal << endl << endl;
}

string LogicalFormula::sknf() {
    string result;
    int counter = 0;

    int numVars = variables.size();
    for (int i = 0; i < (1 << numVars); ++i) {
        int temp = i;
        for (auto& pair : variables) {
            pair.second = temp & 1;
            temp >>= 1;
        }
        bool resultBool = evaluateRPN(infixToRPN(expression));
        if (!resultBool) {
            counter++;
            stringstream ss;
            string term = "";
            for (auto& pair : variables) {
                if (!pair.second) {
                    ss << pair.first;
                }
                else {
                    ss << "!" << pair.first;
                }
                ss << "|";
            }
            term = ss.str();
            term.pop_back();
            result += term;
            result += " & ";
        }
    }
    if (counter == 0) {
        result = "1";
    }
    else {
        result.pop_back();
        result.pop_back();
    }
    return result;
}

string LogicalFormula::sdnf() {
    string result;
    int counter = 0;

    int numVars = variables.size();
    for (int i = 0; i < (1 << numVars); ++i) {
        int temp = i;
        for (auto& pair : variables) {
            pair.second = temp & 1;
            temp >>= 1;
        }
        bool resultBool = evaluateRPN(infixToRPN(expression));
        if (resultBool) {
            counter++;
            stringstream ss;
            string term = "";
            for (auto& pair : variables) {
                if (pair.second) {
                    ss << pair.first;
                }
                else {
                    ss << "!" << pair.first;
                }
                ss << "&";
            }
            term = ss.str();
            term.pop_back();
            result += term;
            result += " | ";
        }
    }
    if (counter == 0) {
        result = "0";
    }
    else {
        result.pop_back();
        result.pop_back();
    }
    return result;
}

const unordered_map<char, bool>& LogicalFormula::getVariables() const {
    return variables;
}