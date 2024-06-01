#include "Matrix.h"


    int Matrix::binaryToInt(const std::vector<int>& binary) const {
        int result = 0;
        for (int bit : binary) {
            result = (result << 1) | bit;
        }
        return result;
    }

    std::vector<int> Matrix::intToBinary(int num, int size) const {
        std::vector<int> binary(size);
        for (int i = size - 1; i >= 0; --i) {
            binary[i] = num & 1;
            num >>= 1;
        }
        return binary;
    }

    Matrix::Matrix() {
        std::srand(std::time(0));

        data.resize(SIZE, std::vector<int>(SIZE));
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                data[i][j] = std::rand() % 2;
            }
        }
    }

    std::vector<int> Matrix::findColumn(int columnIndex) {
        std::vector <int> word;
        for (int i = 0; i < SIZE; ++i) {
            int x = (columnIndex + i) % SIZE;
            word.push_back(data[x][columnIndex]);
        }
        return word;
    }

    std::vector <int> Matrix::showAddressColumn(int position) {
        std::vector <int> diagonal;
        for (int i = 0; i < SIZE; ++i) {
            int rowIndex = (position + i) % SIZE;
            diagonal.push_back(data[rowIndex][i]);
        }
        return diagonal;
    }

    void Matrix::displayLine(std::vector<int> line) {
        for (auto element : line)
            std::cout << element << " ";
        std::cout << std::endl;
    }

    int Matrix::getValue(int row, int col) const {
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            std::cerr << "Error: Index out of bounds" << std::endl;
            return -1;
        }
        return data[row][col];
    }

    void Matrix::display() const {
        for (const auto& row : data) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }

    std::vector<int> Matrix::summa(const std::vector<int>& key) {
        std::vector<int> result;
        int index = -1;

        for (int i = 0; i < SIZE; ++i) {
            std::vector<int> word = findColumn(i);
            if (std::equal(key.begin(), key.end(), word.begin())) {
                result = word;
                index = i;
                break;
            }
        }

        if (index == -1) {
            throw std::invalid_argument("No word starts with the given key.");
        }

        std::vector<int> V(result.begin(), result.begin() + 3);
        std::vector<int> A(result.begin() + 3, result.begin() + 7);
        std::vector<int> B(result.begin() + 7, result.begin() + 11);
        std::vector<int> S(result.begin() + 11, result.end());

        int numA = binaryToInt(A);
        int numB = binaryToInt(B);
        int sum = numA + numB;

        std::vector<int> binarySum = intToBinary(sum, 5);
        result.erase(result.begin() + 11, result.end());
        result.insert(result.end(), binarySum.begin(), binarySum.end());

        return result;
    }

    void Matrix::setWord(int col, const std::vector<int>& word) {
        if (word.size() != SIZE) {
            throw std::invalid_argument("Word size must be 16.");
        }
        for (int i = 0; i < SIZE; i++) {
            int x = (col + i) % SIZE;
            data[x][col] = word[i];
        }
    }

    void Matrix::f0(int col) {
        for (int i = 0; i < SIZE; i++) {
            int x = (col + i) % SIZE;
            data[x][col] = 0;
        }
    }

    void Matrix::f5(int col1, int col2) {
        for (int i = 0; i < SIZE; i++) {
            int x = (col1 + i) % SIZE;
            int y = (col2 + i) % SIZE;
            data[x][col1] = data[y][col2];
        }
    }

    void Matrix::f10(int col1, int col2) {
        for (int i = 0; i < SIZE; i++) {
            int x = (col1 + i) % SIZE;
            int y = (col2 + i) % SIZE;

            if (data[y][col2] == 0)
                data[x][col1] = 1;
            else
                data[x][col1] = 0;
        }
    }

    void Matrix::f15(int col) {
        for (int i = 0; i < SIZE; i++) {
            int x = (col + i) % SIZE;
            data[x][col] = 1;
        }
    }

    std::vector<int> Matrix::findSame(const std::vector<std::optional<bool>>& key) {
        if (key.size() != SIZE) {
            throw std::invalid_argument("Key must consist of 16 elements.");
        }

        std::vector<int> rezKeys;

        for (int j = 0; j < SIZE; ++j) {
            std::vector<int> checkWord = findColumn(j);
            bool same = true;
            for (int i = 0; i < SIZE; ++i) {
                if (!key[i].has_value() || checkWord[i] == key[i].value()) {
                    continue;
                }
                else {
                    same = false;
                    break;
                }
            }
            if (same) {
                rezKeys.push_back(j);
            }
        }

        return rezKeys;
    }

    void Matrix::printMenu() {
        std::cout <<
            "\n1 - display Matrix\n"
            "2 - show a word\n"
            "3 - show adress column\n"
            "4 - get an element\n"
            "5 - sum\n"
            "6 - set a new rod in a column\n"
            "7 - f0\n"
            "8 - f5\n"
            "9 - f10\n"
            "10 - f15\n"
            "11 - search by compliance\n"
            "0 - exit\n";
    }
