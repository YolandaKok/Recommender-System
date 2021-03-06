#ifndef __F_EUCLIDEAN__
#define __F_EUCLIDEAN__

#include <iostream>
#include "F.h"
#include "H.h"

class F_euclidean: public F {
  private:
    int *Rk;
    int tablesize;
    double dimension;
  public:
    F_euclidean(int k, int tablesize, double dimension, double w);
    int hashForPoint(Point *p);
    void generateRk(int k);
    long long int modulo(long long int x, long long y);
    int uniform_distribution(int rangeLow, int rangeHigh);
    int structureSize();
    virtual ~F_euclidean();
};

#endif
