#include <iostream>
#include <random>
#include "Point.h"
#include "H.h"
#include "math.h"
#include <ctime>
#include <chrono>

using namespace std;

/* Constructor of the class H */
H::H(int dimension, int w, double mean, double variance) {
  /* Generate V value for the hash function */
  this->v = generateV(dimension, mean, variance);
  /* Generate t value for the hash function */
  this->t = generateT(0.0, 4.0);
  this->w = w;
  /* Generate Rk and save the values */

}

/* Create function for Point p */
int H::hashForPoint(Point* p) {
  int result;
  result = abs(floor(((p->innerProduct(this->v) + this->t) / this->w)));
  return result;
}

Point* H::generateV(int dimension, double mean, double variance) {
  /* Create a Point */
  Point* p = new Point();
  random_device rd;  //Will be used to obtain a seed for the random number engine
  /* Generate the values for the Vector v using the normal distribution */
  default_random_engine generator(rd());
  normal_distribution<double> distribution(mean, variance);
  double number;
  for ( int i = 0; i < dimension; ++i ) {
    number = distribution(generator);
    p->addCoord(number);
    //cout << number << endl;
  }
  return p;
}

double H::generateT(double mean, double variance) {
  random_device rd;
  default_random_engine generator(rd());
  uniform_real_distribution<double> distribution(mean, variance);
  return distribution(generator);
}

double H::getT() {
  return this->t;
}

Point*& H::getV() {
  return this->v;
}

H::~H() {
  delete this->v;
}
