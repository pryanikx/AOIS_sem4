#include "../LogicalFormulas/LogicalFormula.h"

int main() {
    string expression;
    cout << "Input logical expression: ";
    getline(cin, expression);

    LogicalFormula LogicalFormula(expression);

    LogicalFormula.printTruthTable();

    cout << "\nSKNF: " << LogicalFormula.sknf() << endl;

    cout << "SDNF: " << LogicalFormula.sdnf() << endl;

    return 0;
}