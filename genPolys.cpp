#include "genPolys.h"

// This function generates a random polynomial of user defined 
// degree
// Pre: user defined polynomial degree > 0, initialized vector
// Post: A random polynomial of user defined degree is returned
//       by reference
// Throws: Returns -1 if n <= 0
int genRandomPolys(int n, std::vector<Poly> &polys)
{
   if(n > 0)
   {
      polys.resize(n);
      srand (time(NULL));
      for(int i=0; i<n; i++)
      {
         int coeff = (rand() % 20 + 1)-10;
         polys.at(i).setReal(coeff);
         polys.at(i).setImag(0);
      }
   }
   else
   {
      return -1;
   }
   return 0;
}

// This function generates a polynomial from a user specified file
// Pre: User specified fileName, unsized vector of Poly class
// Post: A user polynomial is generated from the user specified
//       file, returned by reference for efficiency.
// Throws: Returns -1 if n <= 0
//         Returns -2 if Program failed to read specified file
int polysFromFiles(std::string fileName, std::vector<Poly> &polys)
{
   std::string line;
   std::ifstream file (fileName.c_str());
   if(file.is_open())
   {
      getline(file, line);
      int n = atoi(line.c_str());
      polys.resize(n);
      if(n > 0)
      {
         for(int i=0; i<n; i++)
         {
            getline(file, line);
            std::istringstream iss(line);
            std::string token;
            std::getline(iss,token,',');
            polys.at(i).setReal(atoi(token.c_str()));
            std::getline(iss,token,',');
            polys.at(i).setImag(atoi(token.c_str()));
         }
         file.close();
      }
      else
      {
         return -1;
      }
   }
   else
   {
      return -2;
   }
   return 0;
}

// This function outputs the current polynomial to a user specified file name
// in the same format as used to read in polynomials by the polysFromFiles function
// Pre: User defined output file name, a polynomial of size > 0
// Post: A file will be created with the users defined file name
int outputPolyFile(std::string fileName, std::vector<Poly> &polys)
{
   std::ofstream file;
   file.open(fileName.c_str());
   file << std::to_string(polys.size()) + "\n";
   for(int i=0; i<polys.size(); i++)
   {
      file << std::to_string(polys.at(i).getReal()) + "," + std::to_string(polys.at(i).getImag()) + "\n";
   }
   file.close();
   return 0;
}
