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
#include "F_hypercube_euclidean.h"
#include "F_hypercube_cosine.h"

using namespace std;

Hashtable::Hashtable(int size, int k, string lsh_family, int input_size, double dimension) {
  string type1("euclidean");
  string type2("cosine");
  this->k = k;
  this->input_size = input_size;
  this->type = lsh_family;
  this->dimension = dimension;
  if(type1.compare(lsh_family) == 0) {
    /* Initialize f */
    this->f_hash = new F_euclidean(k, size, dimension);
  }
  if(type2.compare(lsh_family) == 0) {
    /* Initialize f */
    this->f_hash = new F_cosine(k, size, dimension);
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

Hashtable::Hashtable(int k, int input_size, int dimension, string lsh_family) {
  string type1("euclidean");
  string type2("cosine");
  this->dimension = dimension;
  this->type = lsh_family;
  this->size = (int)pow(2.0, k);
  this->input_size = input_size;
  if(type1.compare(lsh_family) == 0) {
    /* Initialize f */
    this->f_hash = new F_hypercube_euclidean(k, size, dimension);
    //cout << "eu" << endl;
  }
  if(type2.compare(lsh_family) == 0) {
    /* Initialize f */
    this->f_hash = new F_hypercube_cosine(k, size, dimension);
    //cout << "cos" << endl;
  }
  /* Initialize f */
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
  //cout << bucket_number << endl;
  this->hashtable.at(bucket_number)->push_back(p);
  return 1;
}

int Hashtable::insert(Point *p, int bucket_number) {
  this->hashtable.at(bucket_number)->push_back(p);
  return 1;
}

vector<int> Hashtable::getHFunctions(Point *p) {
  vector<int> hash;
  hash = this->f_hash->getHFun(p);
  return hash;
}

bool Hashtable::empty_list(int bucket_number) {
  if(this->hashtable.at(bucket_number)->empty())
    return true;
  return false;
}

vector<tuple<string, double>> Hashtable::find(int bucket_number, Point*& q, int& count_M, int M_total) {
  /* Create a vector of tuples */
  vector<tuple<string, double>> neighbors;
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

/* Returns points in this bucket */

vector<Point*> Hashtable::find(vector<int> bucket_numbers) {
  vector<Point*> neighbors;

  /*if(empty_list(bucket_number))
    return neighbors;*/
  for( int i = 0; i < bucket_numbers.size(); i++ ) {
    for (std::list<Point*>::const_iterator iterator = this->hashtable.at(bucket_numbers.at(i))->begin(), end = this->hashtable.at(bucket_numbers.at(i))->end(); iterator != end; ++iterator) {
      neighbors.push_back(*iterator);
    }
  }

  return neighbors;
}

Point* Hashtable::exactNN(Point*& q) {
  double distance, final_distance;
  string id;
  Point* exact;
  if(this->type.compare("euclidean") == 0) {
    final_distance = 10000;
  }
  else {
    final_distance = 10000;
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
        exact = *iterator;
      }
    }
  }
  return exact;
}

void Hashtable::points_per_bucket() {
    int count = 0;
  for(int i = 0; i < this->size; i++) {
    cout << "Bucket number: " << i << endl;
    for (std::list<Point*>::const_iterator iterator = this->hashtable.at(i)->begin(), end = this->hashtable.at(i)->end(); iterator != end; ++iterator) {
      //cout << (*iterator)->getId() << endl;
      count++;
    }
    if(count > 0)
        cout << count << endl;
    count = 0;
  }
}

double Hashtable::exactNN(Point*& q, ofstream& output) {
  double distance, final_distance;
  string id;
  const clock_t begin_time = clock();
  clock_t interval;
  //id = this->hashtable.at(0)->front()->getId();
  if(this->type.compare("euclidean") == 0) {
    final_distance = 10000;
  }
  else {
    final_distance = 10000;
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

tuple<string,double,double> Hashtable::find_nearest_neighbor(Point *query) {
  /* Distance and Time */
  tuple<string, double, double> results;
  clock_t begin_time = clock();
  clock_t interval;
  int hash = hash_for_query(query);
  string id;
  double final_distance = 10000.0, distance;
  for (std::list<Point*>::const_iterator iterator = this->hashtable.at(hash)->begin(), end = this->hashtable.at(hash)->end(); iterator != end; ++iterator) {
    if(this->type.compare("euclidean") == 0) {
      int count = 0;
      /* See H for query and for current point in the bucket */
      for(int z = 0; z < this->k; z++) {
        if(f_hash->getH(z)->hashForPoint(query) == f_hash->getH(z)->hashForPoint(*iterator))
          count++;
      }
      if(count == this->k) {
        //cout << "OK" << endl;
        distance = query->euclidean((*iterator));
      }
      else {
        //cout << "NOT OK" << endl;
        //distance = 200000.0;
        distance = query->euclidean((*iterator));
      }

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


vector<Point*> Hashtable::rangeSearch(Point* query, double R, ofstream& output) {
  int hash = hash_for_query(query);
  vector<string> ids;
  double distance;
  vector<Point*> points;
  for (std::list<Point*>::const_iterator iterator = this->hashtable.at(hash)->begin(), end = this->hashtable.at(hash)->end(); iterator != end; ++iterator) {
    if(this->type.compare("euclidean") == 0) {
      distance = query->euclidean((*iterator));
    }
    else {
      distance = query->cosine((*iterator));
    }
    if(distance < R) {
      ids.push_back((*iterator)->getId());
      points.push_back(*iterator);
    }
  }
  return points;
}

int Hashtable::structureSize() {
  return sizeof(class Hashtable) + sizeof(list<Point*>*) * size + sizeof(Point*) * input_size + this->f_hash->structureSize();
}

int Hashtable::getPointsSize() {
  int i = 0;
  for(;;) {
    if(this->hashtable.at(i)->front() != NULL) {
      break;
    }
    i++;
  }
  return this->hashtable.at(i)->front()->structureSize() * input_size;
}

Hashtable::~Hashtable() {
  for(int i = 0; i < this->size; i++)
    delete this->hashtable.at(i);
  delete this->f_hash;
}
