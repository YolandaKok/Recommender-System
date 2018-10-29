#ifndef __HYPERCUBE__
#define __HYPERCUBE__
#include "Hashtable.h"
#include "Point.h"
#include <map>

class Hypercube: public Hashtable {
  private:
    map<int, int> hash_values; /* Map to keep the h functions */
    int probes; /* Number of the probes that we will examine */
    int M; /* Number of points that we will examine */
    string lsh_family;
  public:
    Hypercube(int input_size, int k = 3, int probes = 2, int M = 10, string lsh_family="euclidean");
    int hashForPoint(Point *p);
    int insert_point(Point *p);
    void find_nearest_neighbor(Point *p);
    void findNearest(Point *query, int size, ofstream& output, double R);
    vector<string>& magic(string& str, int i, int changesLeft, vector<string>& strs);
    double smallestDistance(vector<tuple<string,double>>& input, ofstream& output);
    int structureSizeCube();
    int toInt(vector<bool> boolean);
    /* Hash Value for int */
    int hashValue(vector<int> elements);
    //int getHFunctions(Point *p);
    ~Hypercube();
};

#endif
