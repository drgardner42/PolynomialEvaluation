all: genPolys.cpp genPolys.h
	g++ -std=c++11 genPolys.cpp Poly.cpp AlgImpl.cpp PolyAlgsDriver.cpp
