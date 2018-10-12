#ifndef __POINT__
#define __POINT__
#include <vector>
using namespace std;

class Point {
  private:
    /* The length of the point */
    int id;
    int dimension;
    vector<int> coords;
  public:
    Point();
    void addCoord(int coord);
    /* Get Dimensions */
    int getDimension();
    /* Set Id */
    void setId(int id);
    /* Show the list of the coords of the point */
    void print();
    /* Inner Product between two points */
    double innerProduct(Point *p);
    /* Euclidean distance */
    double euclidean(Point *p);
    ~Point();
};

#endif
