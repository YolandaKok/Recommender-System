#include "Hashtable.h"
#include <vector>
#include <list>
#include "Point.h"
#include <iostream>

using namespace std;

Hashtable::Hashtable(int size, Point *p, int k) {
  /* Make it a parameter */
  this->size = size / 2;
  this->hashtable.reserve(this->size);
  /* Initialize the hashtable */
  for(int i = 0; i < this->size; i++)
    this->hashtable.push_back(new list<Point*>);
  /* Initialize f */
  this->f_hash = new F(k);
  //this->hashtable.at(0)->push_back(p);
}

int Hashtable::insert(Point *p) {
  int bucket_number;
  bucket_number = this->f_hash->hashForPoint(this->size, p);
  this->hashtable.at(bucket_number)->push_back(p);
  return 1;
}

Hashtable::~Hashtable() {

}
