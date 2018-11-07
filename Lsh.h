#ifndef __LSH__
#define __LSH__
#include "Hashtable.h"
#include <string>
#include <utility>
#include <random>
#include <vector>

class LSH {
  private:
    int L;
    int k;
    int size;
    double dimension;
    Hashtable **tables;
  public:
    LSH(int L, int size, int k, vector<Point*> points,string lsh_family, int input_size, double dimension);
    void find_nearest_neighbor(Point *query, ofstream& output, int size, double R);
    void bucket();
    vector<string> rangeSearch(Point *query, double R, ofstream& output);
    int structureSize();
    ~LSH();
};

#endif
