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
    int cluster;
    int secondBestCluster;
    bool centroid;
    bool initialCentroid;
  public:
    Point();
    void addCoord(double coord);
    /* Get Dimensions */
    double getDimension();
    /* Set Id */
    void setId(string id);
    string getId();
    int getCluster();
    void setCluster(int cluster);
    /* Show the list of the coords of the point */
    void print();
    /* Inner Product between two points */
    double innerProduct(Point *p);
    bool isCentroid();
    void setCentroid(bool centroid);
    int getSecondBestCluster();
    void setSecondBestCluster(int second);
    /* Euclidean distance */
    double euclidean(Point *p);
    double cosine(Point *p);
    double norm2(Point *p);
    void sumVectors(Point* p);
    void divideVector(int divider);
    bool getInitialCentroid();
    void setInitialCentroid(bool initial);
    bool equalCoords(Point *p);
    int structureSize();
    ~Point();
};

#endif
