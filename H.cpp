#include <iostream>
#include <random>
#include "Point.h"
#include "H.h"
#include "math.h"
#include <ctime>
#include <chrono>

using namespace std;

/* Constructor of the class H */
H::H(int dimension, double mean, double variance) {
  this->v = generateV(dimension, mean, variance);
}

/* Create function for Point p */
int H::hashForPoint(Point* p) {

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
  }
  return p;
}

Point*& H::getV() {
  return this->v;
}
