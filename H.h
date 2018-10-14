#ifndef __H__
#define __H__
#include "Point.h"

class H {
  private:
    Point* v;
    double t;
    int w;
  public:
    H(int dimension, int w, double mean, double variance);
    Point* generateV(int dimension, double mean, double variance);
    double generateT(double mean, double variance);
    int hashForPoint(Point* p);
    ~H();
};

#endif
