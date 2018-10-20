#include "Hashtable.h"
#include <vector>
#include <list>
#include "Point.h"
#include <iostream>
#include <ctime>
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

Hashtable::Hashtable(int k) {
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

bool Hashtable::find(int bucket_number) {
  if(empty_list(bucket_number))
    return false;
  for (std::list<Point*>::const_iterator iterator = this->hashtable.at(bucket_number)->begin(), end = this->hashtable.at(bucket_number)->end(); iterator != end; ++iterator) {
    (*iterator)->print();
  }  //*iterator->getId();
  return true;
}

void Hashtable::points_per_bucket() {
  for(int i = 0; i < this->size; i++) {
    cout << "Bucket number: " << i << endl;
    for (std::list<Point*>::const_iterator iterator = this->hashtable.at(i)->begin(), end = this->hashtable.at(i)->end(); iterator != end; ++iterator) {
      cout << (*iterator)->getId() << endl;
    }
  }
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

Hashtable::~Hashtable() {

}
