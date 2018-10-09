#ifndef __POINT__
#define __POINT__
#include <vector>
using namespace std;

class Point {
  private:
    /* The length of the point */
    int id;
    int dimension;
    vector<double> coords;
  public:
    Point();
    void addCoord(double coord);
    int getDimension();
    /* Set Id */
    /* Show the list of the coords of the point */
    void print();
    ~Point();
};

#endif
