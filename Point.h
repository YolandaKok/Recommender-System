#ifndef __POINT__
#define __POINT__

using namespace std;

class Point {
  private:
    /* The length of the point */
    int dimension;
    double *coords;
  public:
    Point(int, double*);
    int getDimension();
    /* Show the list of the coords of the point */
    void print();
    ~Point();
};

#endif
