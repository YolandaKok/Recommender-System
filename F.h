#ifndef __F__
#define __F__
#include "H.h"
#include <vector>

class F {
  private:
    H** h_functions;
    int k;
  public:
    F(int k);
    virtual int hashForPoint(Point *p);
    int getK();
    H* getH(int i);
    virtual int structureSize();
    void setH(H* h, int i);
    ~F();
};

#endif
