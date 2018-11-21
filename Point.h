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
    int iteration;
    /* R for LSH */
    double R;
    /* List of clusters for the same R */
    vector<int> *clusters;
    double nearestDistance;
    double secondNearestDistance;
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
    int getIteration();
    void setIteration(int iteration);
    /* Show the list of the coords of the point */
    void print(string seperator, ofstream& myfile);
    /* Inner Product between two points */
    double innerProduct(Point *p);
    bool isCentroid();
    void setCentroid(bool centroid);
    int getSecondBestCluster();
    void setSecondBestCluster(int second);
    double getR();
    void setR(double R);
    vector<int>* getClusters();
    /* Euclidean distance */
    double euclidean(Point *p);
    double manhattan(Point *p);
    double cosine(Point *p);
    double norm2(Point *p);
    void sumVectors(Point* p);
    void divideVector(int divider);
    bool getInitialCentroid();
    void setInitialCentroid(bool initial);
    bool equalCoords(Point *p);
    int structureSize();
    double euclidean_squared(Point *p);
    double getNearestDistance();
    double getSecondNearestDistance();
    void setNearestDistance(double nearestDistance);
    void setSecondNearestDistance(double secondNearestDistance);
    ~Point();
};

#endif
