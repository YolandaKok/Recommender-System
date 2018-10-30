#ifndef __POINT__
#define __POINT__
#include <vector>
#include <string>
using namespace std;

//template <typename T1><typename T2>
class Point {
  private:
    /* The length of the point */
    string id;
    int dimension;
    vector<double> coords;
  public:
    Point();
    void addCoord(double coord);
    /* Get Dimensions */
    double getDimension();
    /* Set Id */
    void setId(string id);
    string getId();
    /* Show the list of the coords of the point */
    void print();
    /* Inner Product between two points */
    double innerProduct(Point *p);
    /* Euclidean distance */
    double euclidean(Point *p);
    double cosine(Point *p);
    int structureSize();
    ~Point();
};

#endif
