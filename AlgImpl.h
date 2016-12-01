#include "genPolys.h"
#include <math.h>
#include <vector>
int naivePolyEval(std::vector<Poly>&, std::vector<Poly>&);
int naivePolyEvalCounts(std::vector<Poly> &polys, int64_t&);
void genExponents(Poly base, int n, std::vector<Poly> &result);
void genExponentsNaive(Poly,int,std::vector<Poly>&);
void genExponentsNaiveCounts(Poly,int,std::vector<Poly>&, int64_t&);
int hornerEval(std::vector<Poly>&, std::vector<Poly>&);
int hornerEvalCounts(std::vector<Poly> &polys, int&);
int repeatedSquaringEval(std::vector<Poly>&, std::vector<Poly>&);
int repeatedSquaringEvalCounts(std::vector<Poly>&, int64_t&);
void repeatedSquaringExp(Poly base, int n, std::vector<Poly>&);
void repeatedSquaringExpCounts(Poly base, int n, std::vector<Poly>&, int64_t&);
std::vector<Poly> fft(int, std::vector<Poly>);
std::vector<Poly> fftCount(int, std::vector<Poly>);
int callFFT(std::vector<Poly>&, std::vector<Poly>&);
int callFFTCount(std::vector<Poly>&, int&);
