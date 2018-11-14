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
  this->centroid = false;
  this->initialCentroid = false;
  this->iteration = 0;
}

bool Point::getInitialCentroid() {
    return this->initialCentroid;
}

int Point::getIteration() {
    return this->iteration;
}

void Point::setIteration(int iteration) {
    this->iteration = iteration;
}

bool Point::equalCoords(Point *p) {
    if(this->coords == p->coords) {
        return true;
    }
    else {
        return false;
    }
}

void Point::setInitialCentroid(bool initial) {
    this->initialCentroid = initial;
}


int Point::getSecondBestCluster() {
    return this->secondBestCluster;
}

void Point::setSecondBestCluster(int second) {
    this->secondBestCluster = second;
}


/* Add point into the Vector */
void Point::addCoord(double coord) {
  coords.push_back(coord);
  dimension = (double)coords.size();
}

/* Print data points */
void Point::print() {
  for (auto i = coords.begin(); i != coords.end(); ++i){
    cout << *i << " ";
  }
  cout << endl;
}

/* Get the size of structure in Bytes */
int Point::structureSize() {
  return sizeof(class Point) + (sizeof(double) * coords.size());
}

/* Calculate the inner product between two points */
double Point::innerProduct(Point *p) {
  return inner_product(this->coords.begin(), this->coords.end(), p->coords.begin(), 0.0);
}

void Point::sumVectors(Point* p) {
    transform(this->coords.begin(), this->coords.end(), p->coords.begin(), this->coords.begin(), std::plus<double>());
}

void Point::divideVector(int divider) {
    for(int i = 0; i < this->getDimension(); i++) {
        this->coords.at(i) = (double)this->coords.at(i) / divider;
    }
}

/* Getters */
/* Setters */
void Point::setId(string id) {
  this->id = id;
}

string Point::getId() {
  return this->id;
}

double Point::getDimension() {
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


/* Euclidean distance metric */
double Point::euclidean_squared(Point *p) {
    double result = 0.0;
    double sum = 0.0, temp = 0.0;
    int i;
    for (i = 0; i < this->coords.size(); i++) {
        temp = (this->coords.at(i) - p->coords.at(i)) * (this->coords.at(i) - p->coords.at(i));
        sum = sum + temp;
    }
    return sum;
}

double Point::norm2(Point *p) {
  double sum = 0.0, temp = 0.0;
  for(int i = 0; i < this->coords.size(); i++) {
    temp = (this->coords.at(i) - p->coords.at(i)) * (this->coords.at(i) - p->coords.at(i));
    sum = sum + temp;
  }
  return sum;
}

/* Cosine distance */
double Point::cosine(Point *p) {
  int i;
  double result = 0.0;
  double norm_x = 0.0, norm_y = 0.0;
  for (i = 0; i < this->coords.size(); i++) {
    norm_x += this->coords.at(i) * this->coords.at(i);
    norm_y += p->coords.at(i) * p->coords.at(i);
 }
 norm_x = sqrt(norm_x);
 norm_y = sqrt(norm_y);
  return (1.0 - (this->innerProduct(p) / (norm_x * norm_y)));
}

/* Destructor of the Class Point */
Point::~Point() {
  coords.clear();
}

void Point::setCluster(int cluster) {
    this->cluster = cluster;
}

int Point::getCluster() {
    return this->cluster;
}

bool Point::isCentroid() {
    return this->centroid;
}

void Point::setCentroid(bool centroid) {
    this->centroid = centroid;
}