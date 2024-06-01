#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <bitset>
#include <string>
#include <optional>

class Matrix {
private:
    std::vector<std::vector<int>> data;
    static const int SIZE = 16;

    int binaryToInt(const std::vector<int>& binary) const;

    std::vector<int> intToBinary(int num, int size) const;
public:
    Matrix();
    std::vector<int> findColumn(int columnIndex);
    std::vector <int> showAddressColumn(int position);
    void displayLine(std::vector<int> line);
    int getValue(int row, int col) const;
    void display() const;
    std::vector<int> summa(const std::vector<int>& key);
    void setWord(int col, const std::vector<int>& word);
    void f0(int col);
    void f5(int col1, int col2);
    void f10(int col1, int col2);
    void f15(int col);
    std::vector<int> findSame(const std::vector<std::optional<bool>>& key);
    void printMenu();
};