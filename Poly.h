#include <string>
class Poly
{
   private:
      double real;
      double imag;

   public:
      Poly();
      Poly(double, double);
      void setReal(double r);
      void setImag(double i);
      double getReal();
      double getImag();
      std::string printPoly();
};
