#include <iostream>
#include "F_hypercube.h"
#include <cmath>

using namespace std;

F_hypercube::F_hypercube(int k, int tablesize): F_euclidean(k, tablesize) {

}

int F_hypercube::hashForPoint(Point *p) {
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

F_hypercube::~F_hypercube() {

}
