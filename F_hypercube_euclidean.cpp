#include <iostream>
#include "F_hypercube_euclidean.h"
#include "F_euclidean.h"
#include <cmath>

using namespace std;

F_hypercube_euclidean::F_hypercube_euclidean(int k, int tablesize): F_euclidean(k, tablesize) {

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

F_hypercube_euclidean::~F_hypercube_euclidean() {

}
