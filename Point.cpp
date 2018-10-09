#include <iostream>
#include <vector>
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

/* Getter for dimensions */
/* Setter for dimensions */
/* Destructor of the Class Point */
