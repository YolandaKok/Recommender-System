#include <iostream>
#include "Point.h"
#include "H.h"

using namespace std;

class H_euclidean: public H {
  private:
    double t;
    int w;
  public:
    H_euclidean(int w, int dimension, double mean, double variance);
    /* Redefine hashForPoint */
    int hashForPoint(Point *p);
    double generateT(double mean, double variance);
    double getT();
    ~H_euclidean();
};
