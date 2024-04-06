#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

    class BinaryNumber {
    private:
        int num;
        std::vector<int> dir;
        std::vector<int> rev;
        std::vector<int> add;

    public:
        BinaryNumber(int num);

        void make_direct();

        std::vector<int> getDir();

        void make_rev();

        void make_add();

        std::vector <int> multiply(BinaryNumber other);

        std::vector <int> divide(BinaryNumber& divisor);

        std::vector <int> summary(BinaryNumber& other, std::vector<int>& vec1, std::vector<int>& vec2);

        std::vector <int> summary_dir(BinaryNumber& other);

        std::vector <int> summary_rev(BinaryNumber& other);

        std::vector <int> summary_add(BinaryNumber& other);

        void subtraction(BinaryNumber& other);

        void print();

        std::vector <int> getRev();
    };