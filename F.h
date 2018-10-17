#ifndef __F__
#define __F__
#include "H.h"
#include <vector>

class F {
  private:
    H** h_functions;
    //int* Rk;
    int k;
    //int tablesize;
  public:
    F(int k);
    //void generateRk();
    virtual int hashForPoint(Point *p);
    int getK();
    H* getH(int i);
    void setH(H* h, int i);
    //void printRk();
    //Point* getV();
    ~F();
};

#endif
