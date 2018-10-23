#include "Hashtable.h"
#include <vector>
#include <list>
#include "Point.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <fstream>
#include <tuple>
#include "F_euclidean.h"
#include "F_cosine.h"
#include "F.h"
#include <string>
#include <cmath>
#include "F_hypercube.h"

using namespace std;

Hashtable::Hashtable(int size, int k, string lsh_family) {
  string type1("euclidean");
  string type2("cosine");
  this->k = k;
  this->type = lsh_family;
  if(type1.compare(lsh_family) == 0) {
    /* Initialize f */
    this->f_hash = new F_euclidean(k, size);
  }
  if(type2.compare(lsh_family) == 0) {
    /* Initialize f */
    this->f_hash = new F_cosine(k, size);
  }
  /* Make it a parameter */
  this->size = size;
  this->hashtable.reserve(this->size);
  /* Initialize the hashtable */
  for(int i = 0; i < this->size; i++)
    this->hashtable.push_back(new list<Point*>);
  //this->hashtable.at(0)->push_back(p);
}

int Hashtable::getSize() {
  return this->size;
}

int Hashtable::getK() {
  return this->k;
}

Hashtable::Hashtable(int k, string lsh_family) {
  this->type = lsh_family;
  this->size = (int)pow(2.0, k);
  /* Initialize f */
  this->f_hash = new F_hypercube(k, size);
  /* Make it a parameter */
  this->k = k;
  this->hashtable.reserve(this->size);
  /* Initialize the hashtable */
  for(int i = 0; i < this->size; i++)
    this->hashtable.push_back(new list<Point*>);
  //this->hashtable.at(0)->push_back(p);
}

int Hashtable::insert(Point *p) {
  int bucket_number;
  bucket_number = this->f_hash->hashForPoint(p);
  this->hashtable.at(bucket_number)->push_back(p);
  return 1;
}

bool Hashtable::empty_list(int bucket_number) {
  if(this->hashtable.at(bucket_number)->empty())
    return true;
  return false;
}

vector<tuple<int, double>> Hashtable::find(int bucket_number, Point*& q, int& count_M, int M_total) {
  /* Create a vector of tuples */
  vector<tuple<int, double>> neighbors;
  double distance;
  if(empty_list(bucket_number))
    return neighbors;
  for (std::list<Point*>::const_iterator iterator = this->hashtable.at(bucket_number)->begin(), end = this->hashtable.at(bucket_number)->end(); iterator != end; ++iterator) {
    if(this->type == "euclidean") {
        distance = (*iterator)->euclidean(q);
    }
    else {
        distance = (*iterator)->cosine(q);
    }
    //cout << (*iterator)->euclidean(q) << endl;
    //count_M++;
    neighbors.push_back(make_tuple((*iterator)->getId(), distance));
    /*if(count_M == M_total)
      return neighbors;*/
  }  //*iterator->getId();
  return neighbors;
}

void Hashtable::points_per_bucket() {
  for(int i = 0; i < this->size; i++) {
    cout << "Bucket number: " << i << endl;
    for (std::list<Point*>::const_iterator iterator = this->hashtable.at(i)->begin(), end = this->hashtable.at(i)->end(); iterator != end; ++iterator) {
      cout << (*iterator)->getId() << endl;
    }
  }
}

double Hashtable::exactNN(Point*& q, ofstream& output) {
  double distance, final_distance;
  int id = 0;
  const clock_t begin_time = clock();
  clock_t interval;
  id = this->hashtable.at(0)->front()->getId();
  if(this->type.compare("euclidean") == 0) {
    final_distance = this->hashtable.at(0)->front()->euclidean(q);
  }
  else {
    final_distance = this->hashtable.at(0)->front()->cosine(q);
  }

  for(int i = 0; i < this->size; i++) {
    for (std::list<Point*>::const_iterator iterator = this->hashtable.at(i)->begin(), end = this->hashtable.at(i)->end(); iterator != end; ++iterator) {
      if(this->type.compare("euclidean") == 0) {
        distance = (*iterator)->euclidean(q);
      }
      else {
        distance = (*iterator)->cosine(q);
      }
      if(distance < final_distance) {
        final_distance = distance;
        id = (*iterator)->getId();
      }
    }
  }
  output << "Real Nearest Neighbor: " << id << endl;
  output << "distanceTrue: " << final_distance << endl;
  output << "tTrue: " << double( clock () - begin_time ) /  CLOCKS_PER_SEC  << endl << endl;
  return final_distance;
}

int Hashtable::hash_for_query(Point *query) {
  return this->f_hash->hashForPoint(query);
}

F* Hashtable::getF() {
  return this->f_hash;
}

tuple<int,double,double> Hashtable::find_nearest_neighbor(Point *query) {
  /* Distance and Time */
  tuple<int, double, double> results;
  const clock_t begin_time = clock();
  clock_t interval;
  int hash = hash_for_query(query);
  int id = 0;
  double final_distance = 10000.0, distance;
  for (std::list<Point*>::const_iterator iterator = this->hashtable.at(hash)->begin(), end = this->hashtable.at(hash)->end(); iterator != end; ++iterator) {
    if(this->type.compare("euclidean") == 0) {
      distance = query->euclidean((*iterator));
    }
    else {
      distance = query->cosine((*iterator));
    }
    if(distance < final_distance) {
      final_distance = distance;
      id = (*iterator)->getId();
    }
  }
  results = make_tuple(id, final_distance, double( clock () - begin_time ) /  CLOCKS_PER_SEC);
  return results;
}


vector<int> Hashtable::rangeSearch(Point* query, double R, ofstream& output) {
  int hash = hash_for_query(query);
  vector<int> ids;
  double distance;
  for (std::list<Point*>::const_iterator iterator = this->hashtable.at(hash)->begin(), end = this->hashtable.at(hash)->end(); iterator != end; ++iterator) {
    if(this->type.compare("euclidean") == 0) {
      distance = query->euclidean((*iterator));
    }
    else {
      distance = query->cosine((*iterator));
    }
    if(distance < R) {
      ids.push_back((*iterator)->getId());
    }
  }
  return ids;
}

Hashtable::~Hashtable() {

}
