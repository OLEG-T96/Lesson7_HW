#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;
using std:: string;

enum
{
    num_A = 1,
    num_B,
    equal
};

static int compare(const string &A, const string &B)
{
    unsigned size_A = A.length();
    unsigned size_B = B.length();

    if(size_A == size_B)
      {
        for(unsigned i = 0; i < size_A; ++i)
          {
            if(A[i] != B[i])
              {
                return A[i] > B[i] ? num_A : num_B;
              }
          }
      }
    else
      {
        return size_A >size_B ? num_A : num_B;
      }
    return equal;
}

static bool StrToInt(const string &str, int *mass, size_t size)
{
    if(mass == nullptr)
      {
        return false;
      }
  for(size_t i = 0; i < size; ++i)
     {
       char buf = str[i];
       mass[((size - 1) - i)] = buf - '0';
     }
  return true;
}

static string MassToStr(int *Result_mass,size_t size_Result)
{
    string Result;
    for(unsigned i = 0; i < size_Result; ++i)
       {
          Result += static_cast<char>('0' + Result_mass[((size_Result - 1) - i)]);
       }

    return Result;
}

static string substruct (const string &Number_A, const string &Number_B)
{
    size_t size_Result = Number_A.length();
    int *A_mass = new int[size_Result]{};
    int *B_mass = new int[size_Result]{};

    if(!(StrToInt(Number_A,A_mass,Number_A.length()) &&
          StrToInt(Number_B,B_mass,Number_B.length()) ))
      {
        delete[] A_mass;
        delete[] B_mass;
        return "Error";
      }

    int *Result_mass = new int[size_Result]{};

    for(size_t current_pos = 0; current_pos < size_Result; ++current_pos)
      {
        if(A_mass[current_pos] < B_mass[current_pos])
          {
            Result_mass[current_pos] = (A_mass[current_pos] + 10) - B_mass[current_pos];

            if(A_mass[current_pos+1] == 0)
              {
                size_t digit_pos{1};
                while(A_mass[current_pos + digit_pos] == 0)
                  {
                    digit_pos++;
                  }
                A_mass[current_pos + digit_pos] --;
                for(size_t i = 0; i < digit_pos; ++i)
                  {
                    A_mass[current_pos+i] = 9;
                  }
              }
            else
              {
                A_mass[current_pos+1] --;
              }
          }
        else
          {
            Result_mass[current_pos] = A_mass[current_pos] - B_mass[current_pos];
          }
      }

    while (Result_mass[size_Result - 1] == 0)
       {
         if( size_Result == 1)
           {
             break;
           }
         size_Result-- ;
       }
    string Result = MassToStr(Result_mass,size_Result);
    delete[] A_mass;
    delete[] B_mass;
    delete[] Result_mass;
    return Result;
}

static string sum (const string &Number_A, const string &Number_B)
{
    size_t size_A = Number_A.length();
    size_t size_B = Number_B.length();
    size_t size_Result;

    size_Result = (size_A > size_B) ? size_A + 1 : size_B + 1;

    int *A_mass = new int[size_Result - 1]{};
    int *B_mass = new int[size_Result - 1]{};

     if(!(StrToInt(Number_A,A_mass,size_A) &&
          StrToInt(Number_B,B_mass,size_B) ))
       {
         delete[] A_mass;
         delete[] B_mass;
         return "Error";
       }

     int *Result_mass = new int[size_Result]{};

     for(size_t i = 0; i < (size_Result - 1) ; ++i)
        {
          Result_mass[i] += A_mass[i] + B_mass[i];
          Result_mass[i+1] += (Result_mass[i] / 10);
          Result_mass[i] %= 10;
        }

     if(Result_mass[size_Result - 1] == 0)
       {
         size_Result--;
       }

     string Result = MassToStr(Result_mass,size_Result);
     delete[] A_mass;
     delete[] B_mass;
     delete[] Result_mass;
     return Result;
}

static string multiply (const string &Number_A, const string &Number_B)
{
     size_t size_A = Number_A.length();
     size_t size_B = Number_B.length();
     int *A_mass = new int[size_A]{};
     int *B_mass = new int[size_B]{};

     if(!(StrToInt(Number_A,A_mass,size_A) &&
          StrToInt(Number_B,B_mass,size_B) ))
       {
         delete[] A_mass;
         delete[] B_mass;
         return "Error";
       }

     size_t size_Result = size_A + size_B + 1;
     int *Result_mass = new int[size_Result]{};

     for (size_t A_pos = 0; A_pos < size_A; ++A_pos)
        {
          for (size_t B_pos = 0; B_pos < size_B; ++B_pos)
             {
               Result_mass[A_pos + B_pos] += A_mass[A_pos] * B_mass[B_pos];
             }
        }
     for (size_t i = 0; i < size_Result - 1; ++i)
        {
          Result_mass[i + 1] +=  Result_mass[i] / 10;
          Result_mass[i] %= 10;
        }
     while (Result_mass[size_Result - 1] == 0)
        {
          size_Result-- ;
        }

     string Result = MassToStr(Result_mass,size_Result);
     delete[] A_mass;
     delete[] B_mass;
     delete[] Result_mass;
     return Result;
}

static string Divide (const string &Number, const string &Divisor)
{
      unsigned length = Divisor.length();
      string divident = Number.substr(0,length);
      string result;
      if(compare(divident, Divisor) == num_B) // if(buf < Divisor)
        {
          length++;
          divident = Number.substr(0, (length)); // increase buf
        }
      unsigned digit_pos = 0;

      while((length  + digit_pos) <= Number.length())
        {
          char quoient = '0';
          string buf = divident;

          while((compare(buf,Divisor) == num_A) || //while(buf >= Divisor
                  (compare(buf,Divisor) == equal))
            {
              buf = substruct(buf,Divisor);
              quoient ++;
            }
          string tmp;
          tmp = quoient;
          result += tmp;
          divident = substruct(divident, multiply(Divisor,tmp));

          if(divident == "0")
            {
              divident = Number[length  + digit_pos];
            }
          else
            {
              divident += Number[length  + digit_pos];
            }
          digit_pos++;
        }
      return result;
}

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
   cout<< "Enter your expression 'a + b','a - b',' a * b','a / b' \n" << ">";
   string Number_A, Number_B;
   char operation;
   cin>> Number_A >> operation >> Number_B;

   if( !((InputCheck(Number_A)) && (InputCheck(Number_B))) )
     {
       cout<< "Wrong arguments! " << endl;
       goto Input;
     }

   if(operation == '+')
     {
       cout<< "Result> " << sum(Number_A, Number_B) << endl;
     }

   else if(operation == '*')
     {
       if((Number_A == "0") || (Number_B == "0"))
       {
            cout<< "Result> 0" << endl;
            return 0;
       }
       cout<< "Result> " << multiply(Number_A, Number_B) << endl;
     }

   else if(operation == '-')
     {
       if((compare(Number_A,Number_B) == equal) ||
             (compare(Number_A,Number_B) == num_A))
         {
           cout<< "Result> " << substruct(Number_A, Number_B) << endl;
         }
       else
         {
           string Result = substruct(Number_B, Number_A);
           Result = '-' + Result;
           cout<< "Result> " <<  Result << endl;
         }
     }

   else if(operation == '/')
     {
       if((Number_A == "0") || (Number_B == "0"))
                {
                  cout<< "Division with 0 not allowed! " << endl;
                  goto Input;
                }
       if((compare(Number_A,Number_B) == equal) ||
             (compare(Number_A,Number_B) == num_A))
         {
           cout<< "Result> " << Divide(Number_A, Number_B) << endl;
         }
       else
         {
           cout<< "Result> 0" << endl;
         }
     }

   else
     {
       cout<< "Wrong Operation! " << endl;
       goto Input;
     }

    return 0;
}
