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
      equal,
      num_1,
      num_2,
      both,
      none
  };

bool InputCheck(const string &Number);
int CheckSign(const string &Number_A, const string &Number_B);

int Compare(const string &A, const string &B);
bool StrToInt(const string &str, int *mass, size_t size);
string MassToStr(int *Result_mass,size_t size_Result);
string Substruct (string Num_A, string Num_B);
string Sum (string Number_A, string Number_B);
string Multiply (string Number_A, string Number_B);
string Divide (string Number, string Divisor);
}
