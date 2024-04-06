#include "BinaryNumber.h"

BinaryNumber::BinaryNumber(int num)
{
    this->num = num;
    make_direct();
    make_rev();
    make_add();
}

void BinaryNumber::make_direct() {
    int num_copy = num;
    dir.clear();
    while (num_copy != 1 && num_copy != -1) {
        dir.push_back(std::abs(num_copy % 2));
        num_copy /= 2;
    }
    dir.push_back(1);


    while (dir.size() < 7)
        dir.push_back(0);
    if (num >= 0)
        dir.push_back(0);
    else
        dir.push_back(1);

    std::reverse(dir.begin(), dir.end());
}

std::vector<int> BinaryNumber::getDir()
{
    return dir;
}

void BinaryNumber::make_rev() {
    rev.clear();
    rev.assign(dir.begin(), dir.end());
    if (*rev.begin() == 0)
        exit;
    else
    {
        for (unsigned int i = 1; i < rev.size(); i++)
        {
            if (rev[i] == 0)
                rev[i] = 1;
            else
                rev[i] = 0;
        }
    }
}

void BinaryNumber::make_add() {
    add.clear();
    add.assign(rev.begin(), rev.end());
    if (*add.begin() == 0)
        exit;
    else
    {
        int i = add.size() - 1;
        while (add[i] != 0)
        {
            add[i] = 0;
            i--;
        }
        add[i] = 1;
    }
}

std::vector <int>  BinaryNumber::multiply(BinaryNumber other)
{
    BinaryNumber mult1(abs(num));
    mult1.dir.erase(mult1.dir.begin());
    BinaryNumber mult2(abs(other.num));
    mult2.dir.erase(mult2.dir.begin());
    std::vector<int> multRes(mult1.dir.size() + mult2.dir.size() - 1);

    for (int i = mult1.dir.size() - 1; i >= 0; i--) {
        for (int j = mult2.dir.size() - 1; j >= 0; j--)
            multRes[i + j] += (mult1.dir[i] && mult2.dir[j]);
    }

    for (int i = multRes.size() - 1; i > 0; i--) {
        multRes[i - 1] += multRes[i] / 2;
        multRes[i] %= 2;
    }

    while (multRes[0] > 1) {
        multRes.insert(multRes.begin(), 0);
        multRes[0] += multRes[1] / 2;
        multRes[1] %= 2;
    }
    
    while ((multRes.size() > 8) && (multRes[0] == 0))
    {
        multRes.erase(multRes.begin());
    }

    std::cout << "Multiply: ";
    for (int digit : multRes) {
        std::cout << digit;
    }

    return multRes;
}

std::vector <int> BinaryNumber::divide(BinaryNumber& divisor) {
    std::vector<int> dividend = rev;
    std::vector<int> divisor_vec = divisor.rev;

    int dividend_size = dividend.size();
    int divisor_size = divisor_vec.size();
    int res = num / divisor.num;
    while (dividend.size() < divisor_size)
        dividend.insert(dividend.begin(), 0);
    std::vector<int> remainder(dividend_size, 0);
    BinaryNumber Res(res);
    for (int i = dividend_size - 1; i >= 0; i--) {
        for (int j = 0; j < remainder.size() - 1; j++)
            remainder[j] = remainder[j + 1];
        remainder[remainder.size() - 1] = dividend[i];
        if (remainder[0] == 1) {
            for (int j = 0; j < divisor_size; j++)
                remainder[j] -= divisor_vec[j];
        }
        for (int j = 0; j < remainder.size() - 1; j++) {
            if (remainder[j] < 0) {
                remainder[j] += 2;
                remainder[j + 1] -= 1;
            }
        }
    }
    remainder = Res.dir;
    std::cout << "Remainder: ";
    for (int i = 0; i < remainder.size(); i++) {
        std::cout << remainder[i];
    }
    std::cout << std::endl;

    return remainder;
}

std::vector <int> BinaryNumber::summary(BinaryNumber& other, std::vector<int>& vec1, std::vector<int>& vec2)
{
    std::vector<int> sumRes(vec1.size());

    int carry = 0;
    for (int i = sumRes.size() - 1; i >= 0; --i) {
        sumRes[i] = vec1[i] + vec2[i] + carry;
        if (sumRes[i] == 2) {
            sumRes[i] = 0;
            carry = 1;
        }
        else if (sumRes[i] == 3) {
            sumRes[i] = 1;
            carry = 1;
        }
        else {
            carry = 0;
        }
    }

    return sumRes;
}

std::vector <int> BinaryNumber::summary_dir(BinaryNumber& other)
{
    if (num >= 0 && other.num >= 0)
    {
        dir.insert(dir.begin() + 1, 0);
        other.dir.insert(other.dir.begin() + 1, 0);
        dir.erase(dir.begin());
        other.dir.erase(other.dir.begin());

        std::vector<int> sumRes = summary(other, dir, other.dir);

        if (*sumRes.begin() == 1)
            sumRes.insert(sumRes.begin(), 0);

        std::cout << "Summary: ";
        for (int digit : sumRes) {
            std::cout << digit;
        }
        std::cout << std::endl;
        return sumRes;
    }
    else
        summary_add(other);
}

std::vector <int> BinaryNumber::summary_rev(BinaryNumber& other)
{
    if ((num < 0 && other.num < 0) || (num >= 0 && other.num < 0) || (num < 0 && other.num >= 0))
    {

        rev.insert(rev.begin() + 1, 0);
        other.rev.insert(other.rev.begin() + 1, 0);
        rev.erase(rev.begin());
        other.rev.erase(other.rev.begin());

        std::vector<int> sumRes = summary(other, rev, other.rev);

        if (*sumRes.begin() == 1)
        {
            *sumRes.begin() = 0;
            int i = sumRes.size() - 1;
            while (sumRes[i] != 0)
            {
                sumRes[i] = 0;
                i--;
            }
            sumRes[i] = 1;
        }

        if (*sumRes.begin() == 0)
        {
            while (sumRes[0] == 0)
            {
                sumRes.erase(sumRes.begin());
            }
            if ((num + other.num) < 0)
                sumRes.insert(sumRes.begin(), 1);
            else
                sumRes.insert(sumRes.begin(), 0);
        }

        std::cout << "Summary: ";
        for (int digit : sumRes) {
            std::cout << digit;
        }
        std::cout << std::endl;

        return sumRes;
    }
    else
        summary_dir(other);
}

std::vector <int> BinaryNumber::summary_add(BinaryNumber& other) {
    if (num >= 0 && other.num >= 0)
    {
        summary_dir(other);
        exit;
    }
    else
    {
        int result = num + other.num;

        add.insert(add.begin() + 1, 0);
        other.add.insert(other.add.begin() + 1, 0);
        add.erase(add.begin());
        other.add.erase(other.add.begin());

        std::vector<int> sumRes = summary(other, add, other.add);

        if (result >= 0 && (*sumRes.begin() != 0))
            *sumRes.begin() = 0;
        else
            *sumRes.begin() = 1;

        std::cout << "Summary: ";
        for (int digit : sumRes) {
            std::cout << digit;
        }
        std::cout << std::endl;
        return sumRes;
    }
}

void BinaryNumber::subtraction(BinaryNumber& other)
{
    other.num = -other.num;
    other.make_direct();
    other.make_rev();
    other.make_add();
    summary_add(other);
}

void BinaryNumber::print() {
    std::cout << "Direct: ";
    for (int digit : dir) {
        std::cout << digit;
    }
    std::cout << std::endl;

    std::cout << "Reverse: ";
    for (int digit : rev) {
        std::cout << digit;
    }
    std::cout << std::endl;

    std::cout << "Additional: ";
    for (int digit : add) {
        std::cout << digit;
    }
    std::cout << std::endl;
}

std::vector <int> BinaryNumber::getRev()
{
    return rev;
}