#include "F.h"
#include <iostream>
#include <random>
#include "F_cosine.h"
#include "H_cosine.h"
using namespace std;

F_cosine::F_cosine(int k, int tablesize):F(k) {
  this->tablesize = tablesize;
  /* Create k H_euclidean functions */
  for( int i = 0; i < getK(); i++ ) {
    setH((H_cosine*)new H_cosine(128, 0.0, 1.0), i);
  }
}

int F_cosine::structureSize() {
  return sizeof(class F_cosine) + sizeof(class H_cosine);
}

int F_cosine::hashForPoint(Point *p) {
  int i;
  int z;
  int sum = 0;
  for(i = getK() - 1; i >= 0; i--) {
    sum += (int)pow(2.0, i) * getH(i)->hashForPoint(p);
  }
  return sum;
}

F_cosine::~F_cosine() {

}
