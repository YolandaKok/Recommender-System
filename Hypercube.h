#ifndef __HYPERCUBE__
#define __HYPERCUBE__
#include "Hashtable.h"
#include "Point.h"

class Hypercube: public Hashtable {
  private:
    int probes; /* Number of the probes that we will examine */
    int M; /* Number of points that we will examine */
  public:
    Hypercube(int k = 3, int probes = 2, int M = 10);
    int hashForPoint(Point *p);
    int insert(Point *p);
    void find_nearest_neighbor(Point *p);
    ~Hypercube();
};

#endif
