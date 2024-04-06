#include "Binary32.h"

Binary32::Binary32(double num)
{
    this->num = num;
    signCreating(sign);
    exponentCreating(exponent, num);
    mantissaCreating(mantissa, num);
    binary32Creating(binary32);
}

void Binary32::signCreating(std::vector<int>& sign)
{
    if (num >= 0)
        sign.push_back(0);
    else
        sign.push_back(1);
}

void Binary32::expCount(int& count)
{
    int num_2;
    num_2 = abs(num);
    int exp = 2;
     count = 1;
    while ((exp * 2) <= num_2)
    {
        exp *= 2;
        count++;
    }
    count += 127;
}

void Binary32::exponentCreating(std::vector<int>& exponent, double num)
{
    expCount(count);
    BinaryNumber Exp(count);
    exponent = Exp.getDir();
    exponent.erase(exponent.begin());
}

void Binary32::mantissaCreating(std::vector<int>& mantissa, double num)
{
    num = abs(num);
    int whole = num;
    BinaryNumber Whole(whole);
    mantissa = Whole.getDir();

    while (*mantissa.begin() == 0)
        mantissa.erase(mantissa.begin());
    mantissa.erase(mantissa.begin());

    num -= whole;
    int size = mantissa.size();

    for (int i = 0; i < 23 - size; i++)
    {
        num *= 2;
        if (num >= 1)
        {
            mantissa.push_back(1);
            num -= 1;
        }
        else
            mantissa.push_back(0);
    }
}

void Binary32::binary32Creating(std::vector<int>& binary32)
{
    binary32.push_back(sign[0]);
    for (unsigned int i = 0; i < exponent.size(); i++)
        binary32.push_back(exponent[i]);
    for (unsigned int i = 0; i < mantissa.size(); i++)
        binary32.push_back(mantissa[i]);

    std::cout << "Binary32: ";
    print(binary32);
}

void Binary32::sameQuantity(std::vector<int>& lessExp, std::vector<int>& lessMant, std::vector<int>& biggerExp, int biggerCount, int lessCount)
{
    lessExp = biggerExp;

    biggerCount -= lessCount + 1;
    lessMant.insert(lessMant.begin(), 1);

    for (unsigned int i = 0; i < biggerCount; i++)
        lessMant.insert(lessMant.begin(), 0);
    for (unsigned int i = lessMant.size() - 1; i >= 23; i--)
        lessMant.pop_back();
}

std::vector <int> Binary32::summary(Binary32 other)
{
    int diff_1 = 0, diff_2 = 0;
    if (abs(other.count) < abs(count))
    {
        diff_1++;
        sameQuantity(other.exponent, other.mantissa, exponent, count, other.count);
    }
    else if (abs(other.count) > abs(count))
    {
        diff_2++;
        sameQuantity(exponent, mantissa, other.exponent, other.count, count);
    }

    std::vector<int> sumRes(23);

    int carry = 0;
    for (int i = mantissa.size() - 1; i >= 0; --i) {
        sumRes[i] = mantissa[i] + other.mantissa[i] + carry;
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

    while (carry == 1)
    {
        if (diff_1 == 1)
        {
            other.mantissa.insert(other.mantissa.begin(), 0);
            mantissa.insert(mantissa.begin(), 1);
            sumRes.insert(sumRes.begin(), 0);
            diff_1 = 0;
        }
        else if (diff_2 == 1)
        {
            other.mantissa.insert(other.mantissa.begin(), 1);
            mantissa.insert(mantissa.begin(), 0);
            sumRes.insert(sumRes.begin(), 0);
            diff_2 = 0;
        }
        else
        {
            other.mantissa.insert(other.mantissa.begin(), 0);
            mantissa.insert(mantissa.begin(), 0);
        }

        sumRes[0] = mantissa[0] + other.mantissa[0] + carry;
        if (sumRes[0] == 2) {
            sumRes[0] = 0;
            carry = 1;
            other.mantissa.insert(other.mantissa.begin(), 0);
            mantissa.insert(mantissa.begin(), 0);
            sumRes.insert(sumRes.begin(), 0);
        }
        else if (sumRes[0] == 3) {
            sumRes[0] = 1;
            carry = 1;
            other.mantissa.insert(other.mantissa.begin(), 0);
            mantissa.insert(mantissa.begin(), 0);
            sumRes.insert(sumRes.begin(), 0);
        }
        else {
            carry = 0;
        }
    }
    
    int mult = 2;
    int expInt = 1;
    while ((mult * 2) <= num + other.num)
    {
        mult *= 2;
        expInt++;
    }
    expInt += 127;
    BinaryNumber Exp(expInt);
    exponent = Exp.getDir();
    exponent.erase(exponent.begin());

    for (int i = 7; i >= 0; i--)
        sumRes.insert(sumRes.begin(), exponent[i]);
    if ((num + other.num) >= 0)
        sumRes.insert(sumRes.begin(), 0);
    else
        sumRes.insert(sumRes.begin(), 1);
    while (sumRes.size() > 32)
    {
        sumRes.pop_back();
    }

    std::cout << "Summary: ";
    print(sumRes);

    return sumRes;
}

void Binary32::print(std::vector<int> ieee754)
{
    for (auto digit : ieee754)
        std::cout << digit;
    std::cout << std::endl;
}

std::vector <int> Binary32::getBinary32()
{
    return binary32;
}

std::vector <int> Binary32::getExponent()
{
    return exponent;
}

std::vector <int> Binary32::getMantissa()
{
    return mantissa;
}

std::vector <int> Binary32::getSign()
{
    return sign;
}