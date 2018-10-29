#ifndef __LSH__
#define __LSH__
#include "Hashtable.h"
#include <string>
#include <utility>
#include <random>

class LSH {
  private:
    int L;
    int k;
    int size;
    Hashtable **tables;
  public:
    LSH(int L, int size, int k, vector<Point*> points,string lsh_family, int input_size);
    void find_nearest_neighbor(Point *query, ofstream& output, int size, double R);
    void bucket();
    int structureSize();
    ~LSH();
};

#endif
