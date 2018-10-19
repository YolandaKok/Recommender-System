#ifndef __F_HYPERCUBE__
#define __F_HYPERCUBE__
#include "F_euclidean.h"

class F_hypercube: public F_euclidean {
  private:
  public:
    F_hypercube(int k, int size);
    int hashForPoint(Point *p);
    ~F_hypercube();
};

#endif
