#include <iostream>
#include <random>
#include "Hashutils.h"
#include "Point.h"
#include <math.h>

using namespace std;

/* Calculate the value of h hash function */
int h(Point *p) {
  int w = 4;
  int result;
  Point *v = generateV(p->getDimension(), 0.0, 1.0);
  result = floor((p->innerProduct(v) + generateT(0.0, 4.0)) / w);
  delete v;
  return result;
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
int* generateRk(int k) {
  int i;
  int *array = (int*) malloc(sizeof(int) * k);
  for(i = 0; i < k; i++)
    array[i] = rand() % 19 + (-9);
  return array;
}

/* Calculate the value of the f hash function */
int f(int k, int dataset_size, int* h_array) {
  int TableSize = dataset_size / 4;
  /* Generate the rk values only once */
  int* rk = generateRk(k);
  long long int M = (long long int)pow(2.0, 32.0) - 5, mod, sum = 0;
  /* Calculate the mod values */
  for( int i = 0; i < k; i++ ) {
    /* Check if h_array[i] * rk[i] is negative */
    if( (h_array[i] * rk[i]) < 0 ) {
      cout << h_array[i] * rk[i] << endl;
      mod = (h_array[i] * rk[i]) % M;
      if ((mod < 0) ^ (M < 0)) mod += M;
      cout << "mod " << mod << endl;
      sum += mod;
    }
    else {
      sum += (h_array[i] * rk[i]) % M;
    }
  }

  sum = sum % M;
  sum = sum % TableSize;
  cout << sum  << " sum" << endl;
  free(rk);
  return sum;
}
