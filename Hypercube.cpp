#include "Hypercube.h"
#include "Hashtable.h"
#include <iostream>
#include "Point.h"
#include <string>
#include <cmath>

using namespace std;

/* Constructor for the Hypercube */
Hypercube::Hypercube(int k, int probes, int M):Hashtable(k) {
  this->probes = probes;
  this->M = M;
}

/* Value of h function */
int Hypercube::insert(Point *p) {
  int bucket_number;
  bucket_number = this->hashForPoint(p);
  this->hashtable.at(bucket_number)->push_back(p);
  return 1;
}


int Hypercube::hashForPoint(Point *p) {
  F* f = getF();
  H* h;
  int hash, i, sum = 0;

  for(i = getK() - 1; i >= 0; i--) {
    h = f->getH(i);
    hash = h->hashForPoint(p);
    hash = hash % 2;
    sum += (int)pow(2.0, i) * hash;
  }
  return sum;
}

Hypercube::~Hypercube() {

}
