#include "Hypercube.h"
#include "Hashtable.h"
#include <iostream>
#include "Point.h"

using namespace std;

/* Constructor for the Hypercube */
Hypercube::Hypercube(int k, int probes, int M):Hashtable(k) {
  this->probes = probes;
  this->M = M;
}

/* Hash for point p */



Hypercube::~Hypercube() {

}
