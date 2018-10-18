#ifndef __HASHTABLE__
#define __HASHTABLE__
#include "Point.h"
#include "F.h"
#include <list>
#include <vector>
#include <string>

class Hashtable {
  private:
    vector<list<Point*>*> hashtable;
    int size;
    F *f_hash;
    string type;
  public:
    /* Constructor */
    Hashtable(int size, int k, string lsh_family);
    Hashtable(int k);
    /* Insert point into the hashtable */
    int insert(Point *p);
    bool empty_list(int bucket_number);
    bool traverse(int bucket_number);
    int hash_for_query(Point *query);
    /* Find bucket for query point */
    tuple<int,double,double> find_nearest_neighbor(Point *query);
    /* Traverse the array and find the number of points in each bucket */
    void points_per_bucket();
    int getSize();
    /* Calculate f value: bucket */
    ~Hashtable();
};

#endif
