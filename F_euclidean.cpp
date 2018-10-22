#include "F.h"
#include <iostream>
#include <random>
#include "F_euclidean.h"
#include "H_euclidean.h"
#include <ctime>
using namespace std;

F_euclidean::F_euclidean(int k, int tablesize):F(k) {
  /* Generate Rk */
  generateRk(k);
  this->tablesize = tablesize;
  /* Create k H_euclidean functions */
  for( int i = 0; i < getK(); i++ ) {
    setH((H_euclidean*)new H_euclidean(4, 128, 0.0, 1.0), i);
  }
}

/* Generate Rk values for the euclidean F */
void F_euclidean::generateRk(int k) {
  srand(time(NULL));
  int i;
  random_device rd;  //Will be used to obtain a seed for the random number engine
  default_random_engine generator(rd());
  normal_distribution<double> distribution(0.0, 1.0);
  double number;
  this->Rk = (int*) malloc(sizeof(int) * getK());
  for(i = 0; i < getK(); i++)
    this->Rk[i] = rand() % 100000;
}

int F_euclidean::hashForPoint(Point *p) {
  long long int M = (long long int)pow(2.0, 32.0) - 5, mod, sum = 0;

  for(int i = 0; i < getK(); i++) {
    sum += (getH(i)->hashForPoint(p) * this->Rk[i]) % M;
  }
  //cout << "SUM" << sum << endl;
  sum = sum % M;
  sum = sum % this->tablesize;

  return sum;
}

F_euclidean::~F_euclidean() {
  free(this->Rk);
}
