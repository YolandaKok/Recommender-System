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

Hashtable::Hashtable(int size, int k, string lsh_family, int input_size) {
  string type1("euclidean");
  string type2("cosine");
  this->k = k;
  this->input_size = input_size;
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

Hashtable::Hashtable(int k, int input_size, string lsh_family) {
  string type1("euclidean");
  string type2("cosine");
  this->type = lsh_family;
  this->size = (int)pow(2.0, k);
  this->input_size = input_size;
  if(type1.compare(lsh_family) == 0) {
    /* Initialize f */
    this->f_hash = new F_hypercube_euclidean(k, size);
    cout << "eu" << endl;
  }
  if(type2.compare(lsh_family) == 0) {
    /* Initialize f */
    this->f_hash = new F_hypercube_cosine(k, size);
    cout << "cos" << endl;
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

int Hashtable::structureSize() {
  return sizeof(class Hashtable) + sizeof(list<Point*>*) * size + this->hashtable.at(0)->front()->structureSize( ) * input_size + this->f_hash->structureSize();
}

Hashtable::~Hashtable() {
  cout << "Delete Hashtable" << endl;
  //for()
  for(int i = 0; i < this->size; i++)
    delete this->hashtable.at(i);
  delete this->f_hash;
}
