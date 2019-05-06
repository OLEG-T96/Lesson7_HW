#include <iostream>
#include <cstdlib>
#include "BigNumbers.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::string;

using namespace BigMath;

int main()
{
   Input:
   cout<< "Enter your expression 'a + b','a - b',' a * b','a / b' \n" << ">";
   string Number_A, Number_B;
   char operation;
   cin>> Number_A >> operation >> Number_B;

   if( !((InputCheck(Number_A)) && (InputCheck(Number_B))) )
     {
       cout<< "Wrong arguments! " << endl;
       goto Input;
     }

   switch (operation)
     {
    case '+':
      cout<< "Result> " << Sum(Number_A, Number_B) << endl;
      break;
    case '*':
      cout<< "Result> " << Multiply(Number_A, Number_B) << endl;
      break;
    case '-':
      cout<< "Result> " << Substruct(Number_A, Number_B) << endl;
      break;
    case'/':
      cout<< "Result> " << Divide(Number_A, Number_B) << endl;
      break;
    default:
       cout<< "Wrong Operation! " << endl;
       goto Input;
   }

    return 0;
}

