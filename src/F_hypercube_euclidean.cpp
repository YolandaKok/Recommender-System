#include <iostream>
#include "F_hypercube_euclidean.h"
#include "F_euclidean.h"
#include <cmath>

using namespace std;

F_hypercube_euclidean::F_hypercube_euclidean(int k, int tablesize, double dimension, double w): F_euclidean(k, tablesize, dimension, w) {

}

int F_hypercube_euclidean::hashForPoint(Point *p) {
  int hash, i, sum = 0;
  H *h;
  for(i = 0; i < getK(); i++) {
    h = getH(i);
    hash = h->hashForPoint(p);
    hash = (hash % 2 + 2) % 2;
    //hash = hash % 2;
    sum += (int)pow(2.0, i) * hash;
  }
  return sum;
}

/* Return an array with all the h values */
vector<int> F_hypercube_euclidean::getHFun(Point *p) {
  vector<int> hashvalues;
  H *h;
  int hash;
  for(int i = 0; i < getK(); i++) {
    h = getH(i);
    hash = h->hashForPoint(p);
    hashvalues.push_back(hash);
  }
  return hashvalues;
}

F_hypercube_euclidean::~F_hypercube_euclidean() {

}
