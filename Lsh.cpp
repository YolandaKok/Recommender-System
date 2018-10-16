#include "Lsh.h"
#include "Hashtable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <tuple>
#include "ExactKnn.h"

using namespace std;

/* Constructor for LSH */
LSH::LSH(int L, int size, int k, vector<Point*> points) {
  int i, j;
  this->L = L;
  this->size = size;
  this->k = k;
  this->tables = (Hashtable**)malloc(sizeof(Hashtable*) * L);
  /* Open a file */
  for(i = 0; i < L; i++) {
    this->tables[i] = new Hashtable(size, k);
  }
  /* Insert the points to every hashtable */
  for(i = 0; i < L; i++)
    for(j = 0; j < points.size(); j++)
      this->tables[i]->insert(points.at(j));
}

/* Find Nearest Neighbor in every hashtable */
void LSH::find_nearest_neighbor(Point *query, ofstream& output, vector<Point*> points) {
  int i;
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
  ExactKNN(query, points, output);
}

LSH::~LSH() {
  cout << "Delete lsh" << endl;
  free(this->tables);

}
