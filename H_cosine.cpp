#include <iostream>
#include <random>
#include "Point.h"
#include "H.h"
#include "H_cosine.h"

using namespace std;

H_cosine::H_cosine(int dimension, double mean, double variance):H(dimension, mean, variance) {

}

int H_cosine::hashForPoint(Point *p) {
  double result;
  result = p->innerProduct(getV());
  /* If the inner product is positive or zero */
  if(result >= 0)
    return 1;
  /* If the inner product is negative */
  return 0;
}

H_cosine::~H_cosine() {

}
