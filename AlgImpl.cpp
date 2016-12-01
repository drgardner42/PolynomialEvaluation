#include "AlgImpl.h"

#define PI 3.14159265

// This function implements the naive algorithm for polynomial evaluation
// Pre: A vector of polynomials to evaluate at each of the roots of unity
//      result - a vector to store the results of the naive evaluation in
// Post: All nth roots of unity have been computed naively
// Throws: -1 if no polynomial exists yet
int naivePolyEval(std::vector<Poly> &polys, std::vector<Poly> &result)
{
   int n=polys.size();      
   if (n==0) //Check to see if we have a polynomial
   {
      return -1;
   }
   else
   {
      for(int k=0; k<n; k++)
      {
         //determine root of unity to evaluate at...
         double theta = (2*PI*k)/n;
         Poly curRoot = Poly(cos(theta), sin(theta));
         std::vector<Poly> exponents(n);
         //genExponents(curRoot, n, exponents);
         genExponentsNaive(curRoot, n, exponents);

         double sumR = polys[0].getReal();
         double sumI = polys[0].getImag();

         for(int j=1; j<n; j++)
         {
            Poly curPoly = polys.at(j);
            Poly curExponent = exponents.at(j-1);
            sumR += (curPoly.getReal() * curExponent.getReal()) + ( (-1)*curPoly.getImag()*curExponent.getImag());
            sumI += (curPoly.getReal()*curExponent.getImag()) + (curPoly.getImag()*curExponent.getReal());
         }
         result[k]=Poly(sumR, sumI);
      }
   }
   return 0;
}

// This function is the same as the one above, but keeps track
// of the # of complex multiplies
int naivePolyEvalCounts(std::vector<Poly> &polys, int64_t &count)
{
   int n=polys.size();      
   if (n==0) //Check to see if we have a polynomial
   {
      return -1;
   }
   else
   {
      for(int k=0; k<n; k++)
      {
         //determine root of unity to evaluate at...
         double theta = (2*PI*k)/n;
         Poly curRoot = Poly(cos(theta), sin(theta));
         std::vector<Poly> exponents(n);
         genExponentsNaiveCounts(curRoot, n, exponents, count);

         double sumR = polys[0].getReal();
         double sumI = polys[0].getImag();

         for(int j=1; j<n; j++)
         {
            Poly curPoly = polys.at(j);
            Poly curExponent = exponents.at(j-1);
            if(round(curPoly.getImag())!=0 || round(curExponent.getImag())!=0)
            {
               count++;
            }
            sumR += (curPoly.getReal() * curExponent.getReal()) + ( (-1)*curPoly.getImag()*curExponent.getImag());
            sumI += (curPoly.getReal()*curExponent.getImag()) + (curPoly.getImag()*curExponent.getReal());
         }
         //Poly foo(sumR, sumI);
      }
   }
   return 0;
}

// This function generates all the powers needed for the naive polynomial evaluation iteratively
// using a dynamic programming algorithm (This was my first naive poly exponent builder I made)
// Pre: Base polynomial - the root of unity we are raising to the n-1 power
//                    n - the size of the polynomial
//      Result vector   - Vector of polynomials for the result
// Post: The results vector is populated, containing the values of the root of unity up to n-1 power.
void genExponents(Poly base, int n, std::vector<Poly> &result)
{
   result[0] = base;
   for(int i=1; i<n; i++)
   {
      double prevR = result.at(i-1).getReal();
      double prevI = result.at(i-1).getImag();
      double R = (prevR * base.getReal()) + ((-1)*prevI*base.getImag());
      double I = (prevR * base.getImag()) + (base.getReal() * prevI);
      Poly foo(R, I);
      result.at(i) = foo;
   }
}

// This function generates all powers needed in a more naive way than the dynamic programming
// algorithm above, created to highlight the differences between naive approach & dynamic
// approach
void genExponentsNaive(Poly base, int n, std::vector<Poly> &result)
{
   result[0] = base;
   double baseR = base.getReal();
   double baseI = base.getImag();
   for(int i=1; i<n; i++)
   {
      double R = baseR; 
      double I = baseI;
      for(int j=i; j>0; j--)
      {
         double tempR = R;
         R = R*baseR + (-1)*I*baseI;
         I = tempR*baseI + baseR*I;
      }
      result[i] = Poly(R,I);
   }
}

// This function is the same as above, but keeps track of the # of complex multiplies
void genExponentsNaiveCounts(Poly base, int n, std::vector<Poly> &result, int64_t &count)
{
   result[0] = base;
   double baseR = base.getReal();
   double baseI = base.getImag();
   for(int i=1; i<n; i++)
   {
      double R = baseR; 
      double I = baseI;
      for(int j=i; j>0; j--)
      {
         if(round(I)!=0 || round(baseI)!=0)
         {
            count++;
         }
         /*if(round(I)==0 && round(baseI)==0) {}
         else
         {
            count++;
         }*/
         double tempR = R;
         R = R*baseR + (-1)*I*baseI;
         I = tempR*baseI + baseR*I;
      }
      result[i] = Poly(R,I);
   }
}

// This function implements horners algorithm for polynomial evaluation
// Pre: A vector of polynomials to evaluate at each of the roots of unity
// Post: All nth roots of unity have been computed using horners algorithm 
// Throws: -1 if no polynomial exists yet
int hornerEval(std::vector<Poly> &polys, std::vector<Poly> &result)
{
   int n = polys.size();
   if (n==0) //Check to see if we have a polynomial
   {
      return -1;
   }
   else
   {
      for(int k=0; k<n; k++)
      {
         //determine root of unity to evaluate at...
         double theta = (2*PI*k)/n;
         Poly curRoot = Poly(cos(theta), sin(theta));
         double aReal=0, aImag=0;
         double bReal = polys.at(polys.size()-1).getReal();
         double bImag = polys.at(polys.size()-1).getImag();
         double bRealTemp;
         for(int i=(polys.size()-2); i>-1; i--)
         {
            aReal = polys.at(i).getReal();
            aImag = polys.at(i).getImag();
            bRealTemp = bReal;
            bReal = ((bReal*curRoot.getReal()) + ((-1)*bImag*curRoot.getImag())) + aReal;
            bImag = ((bRealTemp*curRoot.getImag())+(bImag*curRoot.getReal())) + aImag;
         }
         result[k] = Poly(bReal, bImag);
      }
   }
   return 0;
}

// This function is the same as above, but keeps track of the number
// of complex multiplies
int hornerEvalCounts(std::vector<Poly> &polys, int &count)
{
   int n = polys.size();
   if (n==0) //Check to see if we have a polynomial
   {
      return -1;
   }
   else
   {
      for(int k=0; k<n; k++)
      {
         //determine root of unity to evaluate at...
         double theta = (2*PI*k)/n;
         Poly curRoot = Poly(cos(theta), sin(theta));
         double aReal=0, aImag=0;
         double bReal = polys.at(polys.size()-1).getReal();
         double bImag = polys.at(polys.size()-1).getImag();
         double bRealTemp;
         for(int i=(polys.size()-2); i>-1; i--)
         {
            aReal = polys.at(i).getReal();
            aImag = polys.at(i).getImag();
            if(round(aImag)!=0 || round(bImag)!=0)
               count++;
            bRealTemp = bReal;
            bReal = ((bReal*curRoot.getReal()) + ((-1)*bImag*curRoot.getImag())) + aReal;
            bImag = ((bRealTemp*curRoot.getImag())+(bImag*curRoot.getReal())) + aImag;
         }
      }
   }
   return 0;
}

int repeatedSquaringEval(std::vector<Poly> &polys, std::vector<Poly> &result)
{
   int n = polys.size();
   if (n==0) //Check to see if we have a polynomial
   {
      return -1;
   }
   else
   {
      for(int k=0; k<n; k++)
      {
         //determine root of unity to evaluate at...
         double theta = (2*PI*k)/n;
         Poly curRoot = Poly(cos(theta), sin(theta));
         std::vector<Poly> exponents(n);

         repeatedSquaringExp(curRoot, n, exponents);

         double sumR = polys[0].getReal();
         double sumI = polys[0].getImag();

         for(int j=1; j<n; j++)
         {
            Poly curPoly = polys.at(j);
            Poly curExponent = exponents.at(j-1);
            sumR += (curPoly.getReal() * curExponent.getReal()) + ( (-1)*curPoly.getImag()*curExponent.getImag());
            sumI += (curPoly.getReal()*curExponent.getImag()) + (curPoly.getImag()*curExponent.getReal());
         }
         result[k] = Poly(sumR, sumI);
      }
   }
   return 0;
}

int repeatedSquaringEvalCounts(std::vector<Poly> &polys, int64_t &count)
{
   int n = polys.size();
   if (n==0) //Check to see if we have a polynomial
   {
      return -1;
   }
   else
   {
      for(int k=0; k<n; k++)
      {
         //determine root of unity to evaluate at...
         double theta = (2*PI*k)/n;
         Poly curRoot = Poly(cos(theta), sin(theta));
         std::vector<Poly> exponents(n);

         repeatedSquaringExpCounts(curRoot, n, exponents, count);

         double sumR = polys[0].getReal();
         double sumI = polys[0].getImag();

         for(int j=1; j<n; j++)
         {
            Poly curPoly = polys.at(j);
            Poly curExponent = exponents.at(j-1);
            if(round(curPoly.getImag())!=0 || round(curExponent.getImag())!=0)
            {
               count++;
            }
            sumR += (curPoly.getReal() * curExponent.getReal()) + ( (-1)*curPoly.getImag()*curExponent.getImag());
            sumI += (curPoly.getReal()*curExponent.getImag()) + (curPoly.getImag()*curExponent.getReal());
         }
      }
   }
   return 0;
}

void repeatedSquaringExp(Poly base, int n, std::vector<Poly> &result)
{
   result[0] = base;
   double xTwoR = base.getReal()*base.getReal() + (-1)*base.getImag()*base.getImag();
   double xTwoI = base.getReal()*base.getImag() + base.getReal()*base.getImag();
   result[1] = Poly(xTwoR, xTwoI);
   for(int i=3; i<n; i++)
   {
      double R = 0, I=0;
      if(i%2 == 0)
      {
         R = xTwoR;
         I = xTwoI;
         for(int j=0; j<(i/2)-1; j++)
         {
            double tempR = R;
            R = R*xTwoR + (-1)*I*xTwoI;
            I = tempR*xTwoI + xTwoR*I;
         }
      }
      else 
      {
         R = base.getReal();
         I = base.getImag();
         for(int j=0; j<((i-1)/2); j++)
         {
            double tempR = R;
            R = R * xTwoR + (-1)*I*xTwoI;
            I = tempR*xTwoI + xTwoR*I;
         }
      }
      result[i-1] = Poly(R, I);
   }
}

void repeatedSquaringExpCounts(Poly base, int n, std::vector<Poly> &result, int64_t &count)
{
   result[0] = base;
   double xTwoR = base.getReal()*base.getReal() + (-1)*base.getImag()*base.getImag();
   double xTwoI = base.getReal()*base.getImag() + base.getReal()*base.getImag();
   result[1] = Poly(xTwoR, xTwoI);
   for(int i=3; i<n; i++)
   {
      double R = 0, I=0;
      if(i%2 == 0)
      {
         R = xTwoR;
         I = xTwoI;
         for(int j=0; j<(i/2)-1; j++)
         {
            if(round(I)!=0 || round(xTwoI)!=0)
               count++;
            double tempR = R;
            R = R*xTwoR + (-1)*I*xTwoI;
            I = tempR*xTwoI + xTwoR*I;
         }
      }
      else 
      {
         R = base.getReal();
         I = base.getImag();
         for(int j=0; j<((i-1)/2); j++)
         {
            if(round(I)!=0 || round(xTwoI)!=0)
            {
               count++;
            }
            double tempR = R;
            R = R * xTwoR + (-1)*I*xTwoI;
            I = tempR*xTwoI + xTwoR*I;
         }
      }
      result[i-1] = Poly(R, I);
   }
}

int callFFT(std::vector<Poly> &polys, std::vector<Poly> &result)
{
   int n=polys.size();
   if(n==0)
   {
      return -1;
   }
   else
   {
      result = fft(n, polys);
      return 0;
   }
}

int globalCount=0;
int callFFTCount(std::vector<Poly> &polys, int &count)
{
   int n=polys.size();
   if(n==0)
   {
      return -1;
   }
   else
   {
      globalCount=0;
      std::vector<Poly> result = fftCount(n, polys);
      count = globalCount;
      return 0;
   }
}

std::vector<Poly> fft(int n, std::vector<Poly> polys)
{
   if(n==1)
      return polys;
   else
   {
      std::vector<Poly> tempEvens(n/2);
      std::vector<Poly> tempOdds(n/2);
      std::vector<Poly> result(n);
      int countE=0, countO=0;
      for(int i=0; i<n; i++)
      {
         if(i%2 == 0)
         {
            tempEvens.at(countE) = polys[i];
            countE++;
         }
         else
         {
            tempOdds.at(countO) = polys[i];
            countO++;
         }
      }

      std::vector<Poly> evens = fft(n/2, tempEvens);
      std::vector<Poly> odds  = fft(n/2, tempOdds);
      
      for(int k=0; k<(n/2); k++)
      {
         double theta = (2*PI*k)/n;
         double rootReal = cos(theta);
         double rootImag = sin(theta);
         double evenReal = evens[k].getReal();
         double evenImag = evens[k].getImag();
         double oddReal = odds[k].getReal();
         double oddImag = odds[k].getImag();
         result[k] = Poly(evenReal+((rootReal*oddReal)+((-1)*(rootImag*oddImag))), evenImag+((rootReal*oddImag)+(rootImag*oddReal)));
         result[k+(n/2)] = Poly(evenReal-((rootReal*oddReal)+((-1)*(rootImag*oddImag))), evenImag-((rootReal*oddImag)+(rootImag*oddReal)));
      }
      return result;
   }
}

std::vector<Poly> fftCount(int n, std::vector<Poly> polys)
{
   if(n==1)
      return polys;
   else
   {
      std::vector<Poly> tempEvens(n/2);
      std::vector<Poly> tempOdds(n/2);
      std::vector<Poly> result(n);
      int countE=0, countO=0;
      for(int i=0; i<n; i++)
      {
         if(i%2 == 0)
         {
            tempEvens.at(countE) = polys[i];
            countE++;
         }
         else
         {
            tempOdds.at(countO) = polys[i];
            countO++;
         }
      }

      std::vector<Poly> evens = fftCount(n/2, tempEvens);
      std::vector<Poly> odds  = fftCount(n/2, tempOdds);
      
      for(int k=0; k<(n/2); k++)
      {
         double theta = (2*PI*k)/n;
         double rootReal = cos(theta);
         double rootImag = sin(theta);
         double evenReal = evens[k].getReal();
         double evenImag = evens[k].getImag();
         double oddReal = odds[k].getReal();
         double oddImag = odds[k].getImag();
         /*if(oddImag==0 && rootImag==0) {}
         else
            globalCount+=2;*/
         if(round(oddImag)!=0 || round(rootImag)!=0)
            globalCount+=2;
         result[k] = Poly(evenReal+((rootReal*oddReal)+((-1)*(rootImag*oddImag))), evenImag+((rootReal*oddImag)+(rootImag*oddReal)));
         result[k+(n/2)] = Poly(evenReal-((rootReal*oddReal)+((-1)*(rootImag*oddImag))), evenImag-((rootReal*oddImag)+(rootImag*oddReal)));
      }
      return result;
   }
}
