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
    int input_size;
    double dimension;
  public:
    /* Constructor */
    Hashtable(int size, int k, string lsh_family, int input_size, double dimension, double w);
    Hashtable(int k, int input_size, int dimension, double w, string lsh_family = "euclidean");
    /* Insert point into the hashtable */
    int insert(Point *p);
    /* Insert if we have the bucket number */
    int insert(Point *p, int bucket_number);
    bool empty_list(int bucket_number);
    vector<tuple<string, double>> find(int bucket_number, Point*& q, int& count_M, int M_total);
    int hash_for_query(Point *query);
    /* Return h functions */
    vector<int> getHFunctions(Point *p);
    vector<Point*> find(vector<int> bucket_numbers);
    Point* exactNN(Point*& q);
    /* Find bucket for query point */
    tuple<string,double,double> find_nearest_neighbor(Point *query);
    vector<Point*> rangeSearch(Point* q, double R, ofstream& output);
    vector<tuple<double, Point*>> rangeSearchAll(Point* query);
    double exactNN(Point*& q, ofstream& output);
    /* Traverse the array and find the number of points in each bucket */
    void points_per_bucket();
    int getSize();
    F* getF();
    int getK();
    int structureSize();
    int getPointsSize();
    /* Calculate f value: bucket */
    ~Hashtable();
};

#endif
