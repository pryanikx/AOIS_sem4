#include "Matrix.h"

int main() {
    Matrix matrix;

    while (true) {
        matrix.printMenu();
        int choise;
        std::cout << "\nChoose an operation: ";
        std::cin >> choise;

        switch (choise) {
        case 1:
            matrix.display();
            continue;
        case 2: {
            std::cout << "\nInput the index of the column: " << std::endl;
            int n;
            std::cin >> n;
            std::vector<int> line = matrix.findColumn(n);
            matrix.displayLine(line);
            continue;
        }
        case 3: {
            std::cout << "\nInput the index of the starting point row: " << std::endl;
            int n;
            std::cin >> n;
            std::vector<int> line = matrix.showAddressColumn(n);
            matrix.displayLine(line);
            continue;
        }
        case 4: {
            int row = NULL, col = NULL;
            std::cout << "\nInput row index: ";
            std::cin >> row;
            std::cout << "\nInput column index: ";
            std::cin >> col;
            int value = matrix.getValue(row, col);
            std::cout << "\nValue at row " << row << ", column " << col << " is: " << value << std::endl;
            continue;
        }
        case 5: {
            std::vector<int> key;
            bool x;
            std::cout << "Input 3 key bits: ";
            for (int i = 0; i < 3; i++) {
                std::cin >> x;
                key.push_back(x);
            }
            try {
                std::vector<int> result = matrix.summa(key);
                std::cout << "\nSum result: ";
                for (int bit : result) {
                    std::cout << bit;
                }
                std::cout << std::endl;
            }
            catch (const std::invalid_argument& e) {
                std::cerr << e.what() << std::endl;
            }
            break;
        }
        case 6: {
            int index;
            std::cout << "Input the column index to set the word (0-15): ";
            std::cin >> index;

            if (index < 0 || index >= 16) {
                std::cerr << "Invalid column index." << std::endl;
                break;
            }

            std::vector<int> newWord(16);
            std::cout << "Input the new 16-bit word (16 bits separated by spaces): ";
            for (int i = 0; i < 16; ++i) {
                std::cin >> newWord[i];
            }

            try {
                matrix.setWord(index, newWord);
                std::cout << "New word set in column " << index << "." << std::endl;
            }
            catch (const std::invalid_argument& e) {
                std::cerr << e.what() << std::endl;
            }
            break;
        }
        case 7: {
            std::cout << "Where do you want to perform f0? "
                "(input column index): ";
            int col;
            std::cin >> col;
            matrix.f0(col);
            continue;
        }
        case 8: {
            std::cout << "Choose the first and the second argument (2 column indexes): ";
            int col1, col2;
            std::cin >> col1 >> col2;
            matrix.f5(col1, col2);
            continue;
        }
        case 9: {
            std::cout << "Choose the first and the second argument (2 column indexes): ";
            int col1, col2;
            std::cin >> col1 >> col2;
            matrix.f10(col1, col2);
            continue;
        }
        case 10: {
            std::cout << "Where do you want to perform f15? "
                "(input column index): ";
            int col;
            std::cin >> col;
            matrix.f15(col);
            continue;
        }
        case 11: {
            std::vector<std::optional<bool>> key(16);
            bool x;
            char input;
            std::cout << "Input 16 key bits (1/0 for bit values, ? for don't care): ";
            for (int i = 0; i < 16; i++) {
                std::cin >> input;
                if (input == '1') {
                    key[i] = true;
                }
                else if (input == '0') {
                    key[i] = false;
                }
                else if (input == '?') {
                    key[i] = std::nullopt;
                }
                else {
                    std::cerr << "Invalid input." << std::endl;
                    --i;
                }
            }

            try {
                std::vector<int> result = matrix.findSame(key);
                std::cout << "\nMatching column indices: ";
                for (int index : result) {
                    std::cout << index << " ";
                }
                std::cout << std::endl;
            }
            catch (const std::invalid_argument& e) {
                std::cerr << e.what() << std::endl;
            }
            break;
        }
        case 0:
            return 0;
        default:
            std::cout << "\nInput a valid operation number!\n";
        }

    }

    return 0;
}
