#ifndef __F__
#define __F__
#include "H.h"
#include <vector>

class F {
  private:
    H** h_functions;
    int* Rk;
    int k;
    int tablesize;
  public:
    F(int k);
    void generateRk();
    int hashForPoint(int tablesize, Point *p);
    void printRk();
    ~F();
};

#endif
