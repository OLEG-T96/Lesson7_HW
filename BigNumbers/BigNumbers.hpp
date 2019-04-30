#pragma once
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std:: string;

namespace BigMath
{

enum
{
    num_A = 1,
    num_B,
    equal
};

 int compare(const string &A, const string &B);
 bool StrToInt(const string &str, int *mass, size_t size);
 string MassToStr(int *Result_mass,size_t size_Result);
 string substruct (const string &Number_A, const string &Number_B);
 string sum (const string &Number_A, const string &Number_B);
 string multiply (const string &Number_A, const string &Number_B);
 string Divide (const string &Number, const string &Divisor);
}

