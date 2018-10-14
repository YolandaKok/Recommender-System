#ifndef __HASHTABLE__
#define __HASHTABLE__
#include "Point.h"
#include "F.h"
#include <list>
#include <vector>

class Hashtable {
  private:
    vector<list<Point*>*> hashtable;
    int size;
    F *f_hash;
  public:
    /* Constructor */
    Hashtable(int size, Point *p, int k);
    /* Insert point into the hashtable */
    int insert(Point *p);
    ~Hashtable();
};

#endif
