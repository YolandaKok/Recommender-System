#include <iostream>
#include "F.h"
#include "H.h"

class F_euclidean: public F {
  private:
    int *Rk;
    int tablesize;
  public:
    F_euclidean(int k, int tablesize);
    int hashForPoint(Point *p);
    void generateRk(int k);
    ~F_euclidean();
};
