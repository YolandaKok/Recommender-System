#include <random>
#include <iostream>
#include "H.h"
#include "H_euclidean.h"
#include "Point.h"

using namespace std;

extern default_random_engine generator;

H_euclidean::H_euclidean(int w, int dimension, double mean, double variance):H(dimension, mean, variance) {
  this->t = generateT(0.0, 4.0);
  //cout << this->t << endl;
  this->w = 400;
}

int H_euclidean::hashForPoint(Point *p) {
  int result;
  result = floor(((p->innerProduct(getV()) + this->t) / this->w));
  //cout << p->innerProduct(getV()) << endl;
  //cout << p->innerProduct(getV()) << endl;
  return result;
}

double H_euclidean::generateT(double mean, double variance) {
  uniform_real_distribution<double> distribution(mean, variance);
  return distribution(generator);
}

double H_euclidean::getT() {
  return this->t;
}

H_euclidean::~H_euclidean() {
}
