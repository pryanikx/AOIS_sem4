#pragma once
#include "BinaryNumber.h"

    class Binary32
    {
    private:
        double num;
        int count;
        std::vector<int> sign;
        std::vector<int> exponent;
        std::vector<int> mantissa;
        std::vector<int> binary32;
    public:
        Binary32(double num);

        void signCreating(std::vector<int>& sign);

        void expCount(int& count);

        void exponentCreating(std::vector<int>& exponent, double num);

        void mantissaCreating(std::vector<int>& mantissa, double num);

        void binary32Creating(std::vector<int>& binary32);

        void sameQuantity(std::vector<int>& lessExp, std::vector<int>& lessMant, std::vector<int>& biggerExp, int biggerCount, int lessCount);

        std::vector <int> summary(Binary32 other);

        void print(std::vector<int> ieee754);

        std::vector <int> getBinary32();

        std::vector <int> getExponent();

        std::vector <int> getMantissa();

        std::vector <int> getSign();

    };
