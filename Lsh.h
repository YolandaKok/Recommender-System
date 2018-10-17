#ifndef __LSH__
#define __LSH__
#include "Hashtable.h"
#include <string>
#include <utility>

class LSH {
  private:
    int L;
    int k;
    int size;
    Hashtable **tables;
  public:
    LSH(int L, int size, int k, vector<Point*> points, string lsh_family = "euclidean");
    void find_nearest_neighbor(Point *query, ofstream& output, vector<Point*> points);
    ~LSH();
};

#endif
