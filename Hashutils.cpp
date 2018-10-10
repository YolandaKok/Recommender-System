#include <iostream>
#include <random>
#include "Hashutils.h"
#include "Point.h"
#include <math.h>

using namespace std;

/* Calculate the value of h hash function */
int h(Point *p) {
  int w = 4;
  Point *v = generateV(p->getDimension(), 0.0, 1.0);
  return floor((p->innerProduct(v) + generateT(0.0, 4.0)) / w);
}

/* Generate V */
Point* generateV(int dimension, double mean, double variance) {

  /* Create a Point */
  Point *p = new Point();
  /* Generate the values for the Vector v using the normal distribution */
  default_random_engine generator;
  normal_distribution<double> distribution(mean, variance);

  for (int i=0; i < dimension; ++i) {
    double number = distribution(generator);
    p->addCoord(number);
    //cout << number << endl;
  }
  return p;
}

/* Generate number t */
double generateT(double mean, double variance) {
  default_random_engine generator;
  uniform_real_distribution<double> distribution(mean, variance);
  return distribution(generator);
}