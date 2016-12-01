#include "Poly.h"

Poly::Poly() 
{
   real = 0;
   imag = 0;
}
Poly::Poly(double r, double i)
{
   real = r;
   imag = i;
}
void Poly::setReal(double r)
{
   real = r;
}
void Poly::setImag(double i)
{
   imag = i;
}
double Poly::getReal() { return real; }
double Poly::getImag() { return imag; }

std::string Poly::printPoly()
{
   return std::to_string(real) + " + " + std::to_string(imag) + "i";
}
