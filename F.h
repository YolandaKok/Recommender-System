#ifndef __F__
#define __F__
#include "H.h"
#include <vector>

class F {
  private:
    H** h_functions;
    int k;
    double dimension;
  public:
    F(int k, double dimension);
    virtual int hashForPoint(Point *p);
    int getK();
    H* getH(int i);
    virtual int structureSize();
    virtual vector<int> getHFun(Point *p);
    void setH(H* h, int i);
    ~F();
};

#endif
