#include <QCoreApplication>
#include <iostream>
#include <cstdlib>
#include "BigNumbers.hpp"
using std::cin;
using std::cout;
using std::endl;
using std:: string;

using namespace BigMath;

static bool InputCheck(const string &Number)
{
    if(Number.length() == 0)
      {
        return false;
      }
    for(unsigned i = 0; i < Number.length(); ++i)
       {
         if(!((Number[i] >= '0') && (Number[i] <= '9')))
            {
               return false;
            }
       }
    return true;
}


int main()
{
   Input:
   cout<< "Enter your expression 'a + b','a - b',' a * b' \n" << ">";
   string Number_A, Number_B;
   char operation;
   cin>> Number_A >> operation >> Number_B;

   if( !((InputCheck(Number_A)) && (InputCheck(Number_B))) )
     {
       cout<< "Wrong arguments! ";
       goto Input;
     }

   if(operation == '+')
     {
       cout<< "Result> " << sum(Number_A, Number_B);
     }
   else if(operation == '*')
     {
       cout<< "Result> " << multiply(Number_A, Number_B);
     }
   else if(operation == '-')
     {
       if((compare(Number_A,Number_B) == equal) ||
             (compare(Number_A,Number_B) == num_A))
         {
           cout<< "Result> " << substruct(Number_A, Number_B);
         }
       else
         {
           string Result = substruct(Number_B, Number_A);
           Result = '-' + Result;
           cout<< "Result> " <<  Result;
         }

     }
   else if(operation == '/')
     {
       if((compare(Number_A,Number_B) == equal) ||
             (compare(Number_A,Number_B) == num_A))
         {
           cout<< "Result> " << Divide(Number_A, Number_B);
         }
       else
         {
           cout<< "Result> 0";
         }

     }
   else
     {
       cout<< "Wrong Operation! ";
       goto Input;
     }

    return 0;
}
