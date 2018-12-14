#ifndef __F_HYPERCUBE_COSINE__
#define __F_HYPERCUBE_COSINE__
#include "F_cosine.h"

class F_hypercube_cosine: public F_cosine {
  private:
  public:
    F_hypercube_cosine(int k, int size, double dimension);
    //int hashForPoint(Point *p);
    vector<int> getHFun(Point *p);
    ~F_hypercube_cosine();
};

#endif
