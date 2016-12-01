Program was developed on Ubuntu 14.04 by Dustin Gardner

To compile:
   - If you have make - run makefile (tested with GNU Make 3.81)
      - "make"
   - otherwise compile with g++ using the c++11 standard
      - "g++ -std=c++11 genPolys.cpp Poly.cpp AlgImpl.cpp PolyAlgsDriver.cpp"
      - or
      - "g++ -std=c++11 *.cpp"
