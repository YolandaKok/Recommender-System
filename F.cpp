#include "F.h"
#include "H.h"
#include <math.h>
#include <random>
#include <iostream>

using namespace std;

F::F(int k) {
  /* Initialize the h functions */
  this->h_functions = (H**) malloc(sizeof(H*) * k);
  this->k = k;
}

int F::getK() {
  return this->k;
}

H* F::getH(int i) {
  return this->h_functions[i];
}

void F::setH(H* h, int i) {
  this->h_functions[i] = h;
}

int F::hashForPoint(Point* p) {

}

F::~F() {
  cout << "Deleted F function" << endl;
}
