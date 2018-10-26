#ifndef __F_HYPERCUBE__
#define __F_HYPERCUBE__
#include "F_euclidean.h"

class F_hypercube_euclidean: public F_euclidean {
  private:
  public:
    F_hypercube_euclidean(int k, int size);
    int hashForPoint(Point *p);
    ~F_hypercube_euclidean();
};

#endif
