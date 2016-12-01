#include "Poly.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <sstream>
int genRandomPolys(int n, std::vector<Poly> &polys);
int polysFromFiles(std::string fileName, std::vector<Poly> &polys);
int outputPolyFile(std::string fileName, std::vector<Poly> &polys);
