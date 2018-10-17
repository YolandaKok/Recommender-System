#ifndef __H__
#define __H__
#include "Point.h"

class H {
  private:
    Point* v;
    //double t;
    //int w;
  public:
    H(int dimension, double mean, double variance);
    Point* generateV(int dimension, double mean, double variance);
    //double generateT(double mean, double variance);
    virtual int hashForPoint(Point* p);
    /* Getters */
    Point*& getV();
    //double getT();
    //~H();
};

#endif
