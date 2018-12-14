#include "Lsh.h"
#include "Hashtable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <tuple>
#include <cmath>
#include <random>

using namespace std;

/* Constructor for LSH */
LSH::LSH(int L, int size, int k, vector<Point*> points, string lsh_family, int input_size, double dimension, double w) {
  int i, j;
  cout << lsh_family << endl;
  string type1("euclidean");
  string type2("cosine");
  this->L = L;
  this->k = k;
  this->dimension = dimension;
  if(type1.compare(lsh_family) == 0) {
    this->size = size / 4;
  }
  if(type2.compare(lsh_family) == 0) {
    this->size = (int)pow(2.0, k);
  }

  this->tables = (Hashtable**)malloc(sizeof(Hashtable*) * L);
  /* Open a file */
  for(i = 0; i < L; i++) {
    this->tables[i] = new Hashtable(this->size, k, lsh_family, input_size, dimension, w);
  }
  /* Insert the points to every hashtable */
  for(i = 0; i < L; i++)
    for(j = 0; j < points.size(); j++)
      this->tables[i]->insert(points.at(j));
}

/* Find Nearest Neighbor in every hashtable */
void LSH::find_nearest_neighbor(Point *query, ofstream& output, int size, double R) {
  int i;
  static double mean_time_lsh = 0.0;
  static int count = 0;
  static double mean_distance = 0.0, final_mean_distance;
  double real_distance;
  count++;
  vector<tuple<string,double,double>> neighbors;
  vector<string> ids_new;
  vector<Point*> points_new;
  /* Check if R = 0 Approximate NN */
  if(R > 0.0) {
    points_new = rangeSearch(query, R, output);
  }
  /* Vector of tuples */
  vector<tuple<string,double,double>> results;
  tuple<string, double, double> result;
  for(i = 0; i < this->L; i++) {
    result = this->tables[i]->find_nearest_neighbor(query);
    results.push_back(result);
  }
  /* Find the minimum */
  double distance, time_;
  string id;
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
  output << "Nearest neighbor: " << id << endl;
  output << "distanceLSH " <<  distance << endl;
  output << "tLSH " <<  time_ << endl;
  mean_time_lsh += time_;
  real_distance = this->tables[0]->exactNN(query, output);
  /* Print Mean Max Distance */
  final_mean_distance = distance / real_distance;
  if(final_mean_distance > mean_distance) {
    mean_distance = final_mean_distance;
  }
  if(count == size) {
      cout << "Max approximation: " << mean_distance << endl;
      cout << "Mean time for approximate NN: " << mean_time_lsh / size << endl;
      count = 0;
      mean_distance = 0.0;
      final_mean_distance = 0.0;
      mean_time_lsh = 0.0;
  }
}

vector<Point*> LSH::rangeSearch(Point *query, double R, ofstream& output) {
  vector<string> ids;
  vector<string> ids_new;
  int flag = 0, i;
  vector<Point*> points;
  vector<Point*> points_new;

  //output << "Query: Item " << query->getId() << endl;
  //output << "R-nearest Neighbors: " << endl;

  for(i = 0; i < this->L; i++) {
    points = this->tables[i]->rangeSearch(query, R, output);
    /* Make it another function */
    /* Check for double ids into the rangeSearch */
    for(int z = 0; z < points.size(); z++) {
      for(int j = 0; j < points_new.size(); j++) {
        if(points.at(z)->getId() == points_new.at(j)->getId()) {
          flag = 1;
        }
      }
      if(flag == 0)
        points_new.push_back(points.at(z));
      flag = 0;
    }
    points.clear();
  }

  for(int w = 0; w < points_new.size(); w++) {
    //output << "Item " << points_new.at(w)->getId() << endl;
  }
  return points_new;
}

void LSH::bucket() {
   this->tables[0]->points_per_bucket();
}

int LSH::structureSize() {
  cout << "Points " << this->tables[0]->getPointsSize() << " bytes" << endl;
  return sizeof(class LSH) + this->L * this->tables[0]->structureSize() + this->tables[0]->getPointsSize();
}

LSH::~LSH() {
  cout << "Delete lsh" << endl;
  for(int i = 0; i < this->L; i++)
    delete this->tables[i];
  free(this->tables);
}
