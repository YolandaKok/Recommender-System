#include <iostream>
#include "F_hypercube_cosine.h"
#include <cmath>
#include "F_cosine.h"

using namespace std;

F_hypercube_cosine::F_hypercube_cosine(int k, int tablesize): F_cosine(k, tablesize) {

}

/* Return an array with all the h values */
vector<int> F_hypercube_cosine::getHFun(Point *p) {
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

F_hypercube_cosine::~F_hypercube_cosine() {

}
