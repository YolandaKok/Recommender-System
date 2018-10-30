#include "F.h"
#include <iostream>
#include <random>
#include "F_euclidean.h"
#include "H_euclidean.h"
#include <ctime>
#include <functional>
#include "H.h"

using namespace std;

F_euclidean::F_euclidean(int k, int tablesize, double dimension):F(k, dimension) {
  /* Generate Rk */
  generateRk(k);
  this->tablesize = tablesize;
  this->dimension = dimension;
  /* Create k H_euclidean functions */
  for( int i = 0; i < getK(); i++ ) {
    setH((H_euclidean*)new H_euclidean(4, dimension, 0.0, 1.0), i);
  }
}

/* Generate Rk values for the euclidean F */
void F_euclidean::generateRk(int k) {
  int i;
  this->Rk = (int*) malloc(sizeof(int) * getK());
  for(i = 0; i < getK(); i++)
    this->Rk[i] = rand() % (RAND_MAX / 2);
}

int F_euclidean::structureSize() {
  return sizeof(class F_euclidean) + sizeof(int) * getK() + getK() * sizeof(class H_euclidean);
}

int F_euclidean::uniform_distribution(int rangeLow, int rangeHigh) {
    double myRand = rand()/(1.0 + RAND_MAX);
    int range = rangeHigh - rangeLow + 1;
    int myRand_scaled = (myRand * range) + rangeLow;
    return myRand_scaled;
}

int F_euclidean::hashForPoint(Point *p) {
  long long int M = (long long int)pow(2.0, 32.0) - 5, mod, sum = 0;

  for(int i = 0; i < getK(); i++) {
    sum += modulo((getH(i)->hashForPoint(p) * this->Rk[i]), M);
  }

  sum = modulo(sum, M);
  sum = modulo(sum, this->tablesize);

  return sum;
}

long long int F_euclidean::modulo(long long int x, long long y) {
  return (x % y + y) % y;
}

F_euclidean::~F_euclidean() {
  free(this->Rk);
}
