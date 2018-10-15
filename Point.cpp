#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include "Point.h"
#include <math.h>

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
  for (auto i = coords.begin(); i != coords.end(); ++i){
    cout << *i << " ";
  }
  cout << endl;
}

/* Calculate the inner product between two points */
double Point::innerProduct(Point *p) {
  return inner_product(this->coords.begin(), this->coords.end(), p->coords.begin(), 0);
}

/* Getters */
/* Setters */
void Point::setId(int id) {
  this->id = id;
}

int Point::getId() {
  return this->id;
}

int Point::getDimension() {
  return dimension;
}

/* Euclidean distance metric */
double Point::euclidean(Point *p) {
  double result = 0.0;
  double sum = 0.0, temp = 0.0;
  int i;
  for (i = 0; i < this->coords.size(); i++) {
    temp = (this->coords.at(i) - p->coords.at(i)) * (this->coords.at(i) - p->coords.at(i));
    sum = sum + temp;
  }
  result = sqrt(sum);
  return result;
}

/* Destructor of the Class Point */
Point::~Point() {
  /*while(!coords.empty()) {
        delete coords.back();
        coords.pop_back();
    }*/
}
