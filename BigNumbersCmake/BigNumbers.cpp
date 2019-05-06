#include"BigNumbers.hpp"

namespace BigMath {

bool InputCheck(const string &Number)
  {
      if(Number.empty())
        {
          return false;
        }
      for(size_t i = 0; i < Number.length(); ++i)
         {
           if(!((Number[i] >= '0') && (Number[i] <= '9')))
              {
                 if(Number[0] == '-')
                   {
                     continue;
                   }
                 return false;
              }
         }
      return true;
  }

int CheckSign(const string &Number_A, const string &Number_B)
  {
      if((Number_A[0] == '-') && (Number_B[0] == '-'))
        {
          return both;
        }
      else if(Number_A[0] == '-')
        {
          return num_1;
        }
      else if(Number_B[0] == '-')
        {
          return num_2;
        }

      return none;
  }

int Compare(const string &A, const string &B)
  {
      size_t size_A = A.length();
      size_t size_B = B.length();

      if(size_A == size_B)
        {
          for(unsigned i = 0; i < size_A; ++i)
            {
              if(A[i] != B[i])
                {
                  return A[i] > B[i] ? num_1 : num_2;
                }
            }
        }
      else
        {
          return size_A >size_B ? num_1 : num_2;
        }
      return equal;
  }

bool StrToIMass(const string &str, int *mass, size_t size)
  {
      if(mass == nullptr)
        {
          return false;
        }
    for(size_t i = 0; i < size; ++i)
       {
         mass[((size - 1) - i)] = str[i] - '0';
       }
    return true;
  }

string MassToStr(int *Result_mass,size_t size_Result)
  {
      if(Result_mass == nullptr)
        {
          return "Error";
        }
      string Result;
      for(unsigned i = 0; i < size_Result; ++i)
         {
            Result += static_cast<char>('0' + Result_mass[((size_Result - 1) - i)]);
         }

      return Result;
  }

string Substruct (string Num_A, string Num_B)
  {
      if(!(InputCheck(Num_A)) && (InputCheck(Num_B)))
        {
          return "Error";
        }

      bool NegResult{false};

      switch (CheckSign(Num_A,Num_B))
        {
         case num_1 :
           Num_A.erase(0,1);
           return '-' + (Sum(Num_A,Num_B));

         case num_2 :
           Num_B.erase(0,1);
           return Sum(Num_A,Num_B);

         case both :
           Num_A.erase(0,1);
           Num_B.erase(0,1);

           if(Compare(Num_A,Num_B) == num_1)  // if |A| > |B| make B - A
             {
               NegResult = true;
             }
          break;
        }

      string Number_A, Number_B;

      if(Compare(Num_A,Num_B) == num_2)  // if A < B make B - A
        {
          Number_A = Num_B;
          Number_B = Num_A;
          NegResult = true;
        }
      else
        {
          Number_A = Num_A;
          Number_B = Num_B;
        }


      size_t size_Result = Number_A.length();
      int *A_mass = new int[size_Result]{};
      int *B_mass = new int[size_Result]{};

      if(!(StrToIMass(Number_A,A_mass,size_Result) &&
            StrToIMass(Number_B,B_mass,Number_B.length()) ))
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

      if(NegResult)
        {
          return '-' + Result;
        }

      return Result;
  }

string Sum (string Number_A, string Number_B)
  {
      if(!(InputCheck(Number_A)) && (InputCheck(Number_B)))
        {
          return "Error";
        }

      bool NegResult{false};

      switch (CheckSign(Number_A,Number_B))
        {
         case num_1 :
           Number_A.erase(0,1);
           return Substruct(Number_B,Number_A);

         case num_2 :
           Number_B.erase(0,1);
           return Substruct(Number_A,Number_B);

         case both :
           Number_A.erase(0,1);
           Number_B.erase(0,1);
           NegResult = true;
          break;
        }

      size_t size_A = Number_A.length();
      size_t size_B = Number_B.length();

      size_t size_Result = (size_A > size_B) ? size_A + 1 : size_B + 1; // reserve 1 digit if result
                                                                 // is bigger than biggest operand
      int *A_mass = new int[size_Result - 1]{};// create arrays with size of the biggest operand
      int *B_mass = new int[size_Result - 1]{};

       if(!(StrToIMass(Number_A,A_mass,size_A) &&
            StrToIMass(Number_B,B_mass,size_B) ))
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
       if(NegResult)
         {
           return '-' + Result;
         }
       return Result;
  }

string Multiply (string Number_A, string Number_B)
  {
      if(!(InputCheck(Number_A)) && (InputCheck(Number_B)))
        {
          return "Error";
        }

       if((Number_A == "0") || (Number_B == "0"))
         {
           return "0";
         }

       bool NegResult{false};

       switch (CheckSign(Number_A,Number_B))
         {
          case num_1 :
            Number_A.erase(0,1);
            NegResult = true;
            break;

          case num_2 :
            Number_B.erase(0,1);
            NegResult = true;
            break;

          case both :
            Number_A.erase(0,1);
            Number_B.erase(0,1);
           break;
         }

       size_t size_A = Number_A.length();
       size_t size_B = Number_B.length();
       int *A_mass = new int[size_A]{};
       int *B_mass = new int[size_B]{};

       if(!(StrToIMass(Number_A,A_mass,size_A) &&
            StrToIMass(Number_B,B_mass,size_B) ))
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

       if(NegResult)
         {
           return '-' + Result;
         }
       return Result;
  }

string Divide (string Number, string Divisor)
  {
      if(!(InputCheck(Number)) && (InputCheck(Divisor)))
        {
          return "Error";
        }

      if((Number == "0") || (Divisor == "0"))
        {
          return "Division with '0' is not allowed!";
        }
      if(Compare(Number,Divisor) == num_2)
        {
          return "0";
        }

      bool NegResult{false};

      switch (CheckSign(Number,Divisor))
        {
         case num_1 :
           Number.erase(0,1);
           NegResult = true;
           break;

         case num_2 :
           Divisor.erase(0,1);
           NegResult = true;
           break;

         case both :
           Number.erase(0,1);
           Divisor.erase(0,1);
          break;
        }

        size_t length = Divisor.length();
        string divident = Number.substr(0,length);
        string result;

        if(Compare(divident, Divisor) == num_2) // if(buf < Divisor)
          {
            length++;
            divident = Number.substr(0, (length)); // increase buf
          }
        unsigned digit_pos = 0;

        while((length  + digit_pos) <= Number.length())
          {
            char quoient = '0';
            string buf = divident;

            while((Compare(buf,Divisor) == num_1) || //while(buf >= Divisor
                    (Compare(buf,Divisor) == equal))
              {
                buf = Substruct(buf,Divisor);
                quoient++;
              }
            string tmp;
            tmp = quoient;
            result += tmp;
            divident = Substruct(divident, Multiply(Divisor,tmp));

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
        if(NegResult)
          {
            return '-' + result;
          }
        return result;
  }
}
