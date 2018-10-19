#include "Hypercube.h"
#include "Hashtable.h"
#include <iostream>
#include "Point.h"
#include <string>
#include <cmath>
#include <bitset>

using namespace std;

/* Constructor for the Hypercube */
Hypercube::Hypercube(int k, int probes, int M):Hashtable(k) {
  this->probes = probes;
  this->M = M;
}

/* Value of h function */
int Hypercube::insert_point(Point *p) {
  insert(p);
}

void Hypercube::findNearest(Point *query) {
  int hash = hash_for_query(query);
  int k = getK();
  int result, i;
  cout << hash << endl;
  char* str = (char*)malloc(sizeof(char) * k);
  for(i = 0; i < k; i++) {
    result = hash % 2;
    hash = hash / 2;
    cout << "result" << result << endl;
    cout << "hash" << hash << endl;
    str[k-1-i] = result;
  }
  cout << str[0] << endl;
  free(str);
  /* Find the hamming distance and check into these buckets */

}

Hypercube::~Hypercube() {

}
