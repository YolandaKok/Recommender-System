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
  static default_random_engine generator;
  normal_distribution<double> distribution(mean, variance);
  double number;
  for (int i=0; i < dimension; ++i) {
    number = distribution(generator);
    p->addCoord(number);
    //cout << number << endl;
  }
  return p;
}

/* Generate number t */
double generateT(double mean, double variance) {
  static default_random_engine generator;
  uniform_real_distribution<double> distribution(mean, variance);
  return distribution(generator);
}

/* Generate rk values */
static int* generateRk(int k) {
  int i;
  int *array = (int*) malloc(sizeof(int) * k);
  for(i = 0; i < k; i++)
    array[i] = rand() % 19 + (-9);
  return array;
}

/* Calculate the value of the f hash function */
int f(int k, int dataset_size) {
  int TableSize = dataset_size / 4;
  /* Generate k values for r */
  default_random_engine generator;
  uniform_real_distribution<double> distribution(0.0, 10.0);

  static int* array = generateRk(k);
  for(int i = 0; i < k; i++)
    cout << array[i] << endl;
}
