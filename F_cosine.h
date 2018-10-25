#ifndef __F_COSINE__
#define __F_COSINE__

#include <iostream>
#include "F.h"
#include "H_cosine.h"
#include "H.h"

class F_cosine: public F {
  private:
    int tablesize;
  public:
    F_cosine(int k, int tablesize);
    int hashForPoint(Point *p);
    int structureSize();
    ~F_cosine();
};
#endif
