#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#include "Point.h"
using namespace std;
/* Constructor of the Class Point */
Point::Point() {
  this->dimension = 0;
}
/* Add point into the Vector */
void Point::addCoord(double coord) {
  coords.push_back(coord);
  dimension = coords.size();
}

/* Print data points */
void Point::print() {
  for (auto i = coords.begin(); i != coords.end(); ++i)
          cout << *i << " ";
          cout << endl;
}

/* Calculate the inner product between two points */
double Point::innerProduct(Point *p) {
  return inner_product(this->coords.begin(), this->coords.end(), p->coords.begin(), 0.0);
}

/* Getters */
/* Setters */
void Point::setId(int id) {
  this->id = id;
}
/* Destructor of the Class Point */
