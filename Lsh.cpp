#include "Lsh.h"
#include "Hashtable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <tuple>
#include "ExactKnn.h"
#include <cmath>

using namespace std;

/* Constructor for LSH */
LSH::LSH(int L, int size, int k, vector<Point*> points, string lsh_family) {
  int i, j;

  string type1("euclidean");
  string type2("cosine");
  this->L = L;
  this->k = k;
  if(type1.compare(lsh_family) == 0) {
    this->size = size / 4;
  }
  if(type2.compare(lsh_family) == 0) {
    this->size = (int)pow(2.0, k);
    cout << "size cosine " << this->size << endl;
  }

  this->tables = (Hashtable**)malloc(sizeof(Hashtable*) * L);
  /* Open a file */
  for(i = 0; i < L; i++) {
    this->tables[i] = new Hashtable(this->size, k, lsh_family);
  }
  /* Insert the points to every hashtable */
  for(i = 0; i < L; i++)
    for(j = 0; j < points.size(); j++)
      this->tables[i]->insert(points.at(j));
}

/* Find Nearest Neighbor in every hashtable */
void LSH::find_nearest_neighbor(Point *query, ofstream& output, vector<Point*> points) {
  int i;
  static double mean_time_lsh = 0.0;
  static int count = 0;
  count++;
  output << "item " << query->getId() << endl;
  /* Vector of tuples */
  vector<tuple<int,double,double>> results;
  tuple<int, double, double> result;
  for(i = 0; i < this->L; i++) {
    result = this->tables[i]->find_nearest_neighbor(query);
    results.push_back(result);
  }
  /* Find the minimum */
  double distance, time_;
  int id;
  id = get<0>(results.at(0));
  distance = get<1>(results.at(0));
  time_ = get<2>(results.at(0));
  for(i = 0; i < results.size(); i++) {
    if(get<1>(results.at(i)) < distance) {
      id = get<0>(results.at(i));
      distance = get<1>(results.at(i));
      time_ = get<2>(results.at(i));
    }
  }
  output << "R-near neighbors" << endl;
  output << "item " << id << endl;
  output << "distanceLSH " <<  distance << endl;
  output << "tLSH " <<  time_ << endl;
  mean_time_lsh += time_;
  ExactKNN(query, points, output);
  if(count == 99)
    output << "Mean Lsh " << mean_time_lsh / 100.0 << endl;
}

void LSH::bucket() {
   this->tables[0]->points_per_bucket();
}

LSH::~LSH() {
  cout << "Delete lsh" << endl;
  free(this->tables);

}
