#include <random>
#include <iostream>
#include "H.h"
#include "H_euclidean.h"
#include "Point.h"

using namespace std;

H_euclidean::H_euclidean(int w, int dimension, double mean, double variance):H(dimension, mean, variance) {
  this->t = generateT(0.0, 4.0);
  this->w = 300;
}

int H_euclidean::hashForPoint(Point *p) {
  int result;
  result = floor(((p->innerProduct(getV()) + this->t) / this->w));
  return result;
}

double H_euclidean::generateT(double mean, double variance) {
  random_device rd;
  default_random_engine generator(rd());
  uniform_real_distribution<double> distribution(mean, variance);
  return distribution(generator);
}

double H_euclidean::getT() {
  return this->t;
}

H_euclidean::~H_euclidean() {

}
