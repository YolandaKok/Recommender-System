#ifndef __HASHTABLE__
#define __HASHTABLE__
#include "Point.h"
#include "F.h"
#include <list>
#include <vector>

class Hashtable {
  private:
    vector<list<Point*>*> hashtable;
    int size;
    F *f_hash;
  public:
    /* Constructor */
    Hashtable(int size, Point *p, int k);
    /* Insert point into the hashtable */
    int insert(Point *p);
    bool empty_list(int bucket_number);
    bool traverse(int bucket_number);
    int hash_for_query(Point *query);
    /* Find bucket for query point */
    bool find_nearest_neighbor(Point *query);
    /* Traverse the array and find the number of points in each bucket */
    void points_per_bucket();
    /* Calculate f value: bucket */
    ~Hashtable();
};

#endif
