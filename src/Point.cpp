#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include "Point.h"
#include <math.h>
#include <fstream>

using namespace std;
/* Constructor of the Class Point */
Point::Point() {
  this->dimension = 0;
  this->centroid = false;
  this->initialCentroid = false;
  this->iteration = 0;
  this->R = 0.0;
  this->clusters = new vector<int>;
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

void Point::modifyCoord(int index, double value) {
    this->coords.at(index) += value;
}

void Point::addModified(int index) {
    this->modified.push_back(index);
}

void Point::subtractAverage() {
    // Subtract from the modified
    for( int i = 0; i < this->modified.size(); i++ ) {
        this->coords.at(this->modified.at(i)) -= this->average;
    }
}

void Point::computeAverage() {
    double sum = 0.0;
    // Calculate Sum
    for( int i = 0; i < this->modified.size(); i++ ) {
        sum += this->coords.at(this->modified.at(i));
    }
    sum /= this->modified.size();
    this->average = sum;
}

bool Point::findModified(int index) {
    vector<int>::iterator it;
    it = find (this->modified.begin(), this->modified.end(), index);
    if (it != this->modified.end())
        return true;
    else
        return false;
}

void Point::printModified() {
    for( int i = 0; i < this->modified.size(); i++ ) {
        cout << this->modified.at(i) << " ";
    }
    cout << endl;
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
void Point::print(string seperator, ofstream& myfile) {
    //cout.precision(20);
  myfile << "[ ";
  for (auto i = coords.begin(); i != coords.end(); ++i){
    myfile << *i << seperator;
  }
  myfile << "]";
  //cout << endl;
}

void Point::print() {
    cout.precision(20);
    cout << "[ ";
    for (auto i = coords.begin(); i != coords.end(); ++i){
        cout << *i << " ";
    }
    cout << "]";
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

double Point::getCoord(int index) {
    return this->coords.at(index);
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

double Point::manhattan(Point *p) {
    double result = 0.0;
    double sum = 0.0, temp = 0.0;
    for(int i = 0; i < this->coords.size(); i++) {
        temp = abs(this->coords.at(i) - p->coords.at(i));
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

/* Cosine distance */
double Point::cosine_similarity(Point *p) {
    int i;
    double result = 0.0;
    double norm_x = 0.0, norm_y = 0.0;
    for (i = 0; i < this->coords.size(); i++) {
        norm_x += this->coords.at(i) * this->coords.at(i);
        norm_y += p->coords.at(i) * p->coords.at(i);
    }
    norm_x = sqrt(norm_x);
    norm_y = sqrt(norm_y);
    return (this->innerProduct(p) / (norm_x * norm_y));
}

double Point::getAverage() {
    return this->average;
}

double Point::euclidean_similarity(Point *p) {
    return 1.0 / (1.0 + this->euclidean(p));
}

/* Destructor of the Class Point */
Point::~Point() {
  coords.clear();
  delete this->clusters;
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

double Point::getR() {
    return this->R;
}

void Point::setR(double R) {
    this->R = R;
}

vector<int>* Point::getClusters() {
    return this->clusters;
}

void Point::setClusters(int j) {
    this->clusters->push_back(j);
}

double Point::getNearestDistance() {
    return this->nearestDistance;
}

double Point::getSecondNearestDistance() {
    return this->secondNearestDistance;
}

void Point::setNearestDistance(double nearestDistance) {
    this->nearestDistance = nearestDistance;
}

void Point::setSecondNearestDistance(double secondNearestDistance) {
    this->secondNearestDistance = secondNearestDistance;
}