#ifndef __HASHTABLE__
#define __HASHTABLE__
#include "Point.h"
#include "F.h"
#include <list>
#include <vector>
#include <string>
#include <tuple>
#include <fstream>

class Hashtable {
  private:
    vector<list<Point*>*> hashtable;
    int size;
    F *f_hash;
    string type;
    int k;
  public:
    /* Constructor */
    Hashtable(int size, int k, string lsh_family);
    Hashtable(int k, string lsh_family = "euclidean");
    /* Insert point into the hashtable */
    int insert(Point *p);
    bool empty_list(int bucket_number);
    vector<tuple<int, double>> find(int bucket_number, Point*& q, int& count_M, int M_total);
    int hash_for_query(Point *query);
    /* Find bucket for query point */
    tuple<int,double,double> find_nearest_neighbor(Point *query);
    vector<int> rangeSearch(Point* q, double R, ofstream& output);
    double exactNN(Point*& q, ofstream& output);
    /* Traverse the array and find the number of points in each bucket */
    void points_per_bucket();
    int getSize();
    F* getF();
    int getK();
    int structureSize();
    /* Calculate f value: bucket */
    ~Hashtable();
};

#endif
