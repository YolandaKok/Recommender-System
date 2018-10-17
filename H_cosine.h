#ifndef __H_COSINE__
#define __H_COSINE__

#include <iostream>
#include "Point.h"

using namespace std;

class H_cosine: public H {
  public:
    H_cosine(int dimension, double mean, double variance);
    int hashForPoint(Point *p);
    ~H_cosine();
};
#endif
