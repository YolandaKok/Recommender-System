#ifndef __HASHUTILS_
#define __HASHUTILS_
#include "Point.h"

using namespace std;
/* h(p) hash function */
int h(Point *p);
/* Create f(p) */
/* Array of hash functions int's */
int f();
Point* generateV(int dimension, double mean, double variance);
double generateT(double mean, double variance);
#endif
