/*******************************************************
* Comparison of various polynomial evaluation algorithms
* Author: Dustin Gardner
* Created: 11/5/16 - 11/20/16
*
* Pass by reference is utilized heavily to lower execution 
* times throughout program.
*/


#include "AlgImpl.h"
#include <ctime>

void printMenu();

int main()
{
   bool goAgain = true;
   int choice;
   std::vector<Poly> polys;
   std::vector<Poly> result;
   while(goAgain)
   {
      printMenu();
      std::cout << "Please pick a menu option: ";
      std::cin >> choice;
      if(choice==1)
      {
         bool innerGoAgain = true;
         while(innerGoAgain)
         {
            int n;
            std::cout << "Please input the desired polynomial size: ";
            std::cin >> n;
            if(genRandomPolys(n, polys) == 0)
            {
               innerGoAgain = false;
            }
            else
            {
               std::cout << "Please input n > 0!" << std::endl;
            }
         }
      }
      else if(choice==2)
      {
         std::string fileName;
         std::cin.ignore(80, '\n');
         std::cout << "What is the filename? " ;
         getline(std::cin, fileName);
         int retVal = polysFromFiles(fileName, polys);
         if(retVal == -1)
         {
            std::cout << "Specified file has n <= 0\n" << std::endl;
         }
         if(retVal == -2)
         {
            std::cout << "Error processing specified file " << std::endl;
         }
      }
      else if(choice==3)
      {
         std::string fileName;
         std::cin.ignore(80, '\n');
         std::cout << "Please name the output file: ";
         getline(std::cin, fileName);
         outputPolyFile(fileName, polys);
      }
      else if(choice==4)
      {  
         result.resize(polys.size());
         if(naivePolyEval(polys, result) < 0)
         {
            std::cout << "Please generate a polynomial before using this option" << std::endl;
         }
         else
         {
            for(int i=0; i<result.size(); i++)
            {
               std::cout << result.at(i).printPoly() << std::endl;
            }
         }
      }
      else if(choice==5)
      {
         result.resize(polys.size());
         if(hornerEval(polys, result) < 0)
         {
            std::cout << "Please generate a polynomial before using this option" << std::endl;
         } 
         else
         {
            for(int i=0; i<result.size(); i++)
            {
               std::cout << result.at(i).printPoly() << std::endl;
            }
         }
      }
      else if(choice==6)
      {
         result.resize(polys.size());
         if(repeatedSquaringEval(polys, result) < 0)
         {
            std::cout << "Please generate a polynomial before using this option" << std::endl;
         }
         else
         {
            for(int i=0; i<result.size(); i++)
            {
               std::cout << result.at(i).printPoly() << std::endl;
            }
         }
      }
      else if(choice==7)
      {
         result.resize(polys.size());
         if(callFFT(polys, result) < 0)
         {
            std::cout << "Please generate a polynomial before using this option" << std::endl;
         }
         else
         {
            for(int i=0; i<result.size(); i++)
            {
               std::cout << result.at(i).printPoly() << std::endl;
            }
         }
      }
      else if(choice==8)
      {
         if(polys.size() == 0)
         {
            std::cout << "Please generate a polynomial before using this option" << std::endl;
         }
         else
         {
            result.resize(polys.size());
            clock_t begin_time = clock();
            naivePolyEval(polys, result);
            std::cout << "Naive  Eval           : " <<  float( clock () - begin_time ) /  CLOCKS_PER_SEC << std::endl;
            begin_time = clock();
            hornerEval(polys,result);
            std::cout << "Horner Eval           : " <<  float( clock () - begin_time ) /  CLOCKS_PER_SEC << std::endl;
            begin_time = clock();
            repeatedSquaringEval(polys, result);
            std::cout << "Repeated Squaring Eval: " <<  float( clock () - begin_time ) /  CLOCKS_PER_SEC << std::endl;
            begin_time = clock();
            callFFT(polys, result);
            std::cout << "FFT Eval              : " <<  float( clock () - begin_time ) /  CLOCKS_PER_SEC << std::endl;
         }
      }
      else if(choice==9)
      {
         if(polys.size() == 0)
         {
            std::cout << "Please generate a polynomial before using this option" << std::endl;
         }
         else
         {
            int count=0;
            int64_t count64=0;
            naivePolyEvalCounts(polys, count64);
            std::cout << "Naive Eval             : " << count64 << std::endl;

            count=0;
            hornerEvalCounts(polys, count);
            std::cout << "Horner Eval            : " << count << std::endl;

            count64=0;
            repeatedSquaringEvalCounts(polys, count64);
            std::cout << "Repeated Squaring Eval : " << count64 << std::endl;

            count=0;
            callFFTCount(polys, count);
            std::cout << "FFT Eval               : " << count << std::endl;
         }
      }
      else if(choice==10)
      {
         return 0;
      }
      else if(choice==11)
      {
         for(int i=0; i<polys.size(); i++)
         {
            std::cout << polys.at(i).printPoly() << std::endl;
         }
      }
      else
      {
         std::cout << "Invalid menu choice" << std::endl;
      }
   }
}

void printMenu()
{
   std::cout << "*************************************************" << std::endl;
   std::cout << "*                    MENU                       *" << std::endl;
   std::cout << "* 1) Generate a random Polynomial               *" << std::endl;
   std::cout << "* 2) Read in Polynomial from Input File         *" << std::endl;
   std::cout << "* 3) Output Polynomial to File                  *" << std::endl;
   std::cout << "* 4) Run naive polynomial evaluation algorithm  *" << std::endl;
   std::cout << "* 5) Run Horner's polynomial evaluation alg     *" << std::endl;
   std::cout << "* 6) Run naive using repeated squaring          *" << std::endl;
   std::cout << "* 7) Run evaluation using FFT algorithm         *" << std::endl;
   std::cout << "* 8) Time the running time of all 4 algorithms  *" << std::endl;
   std::cout << "* 9) Count the number of complex * in each alg  *" << std::endl;
   std::cout << "* 10) Quit Program                              *" << std::endl;
   std::cout << "*                                               *" << std::endl;
   std::cout << "*************************************************" << std::endl;
   std::cout << std::endl;
}
