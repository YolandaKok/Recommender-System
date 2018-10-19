#include "Hypercube.h"
#include "Hashtable.h"
#include <iostream>
#include "Point.h"
#include <string>
#include <cmath>
#include <bitset>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

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
  char z;
  cout << hash << endl;
  char *str = (char*)malloc(3);
  string str1;
  str1.resize(k);
  for(i = 0; i < k; i++) {
    result = hash % 2;
    hash = hash / 2;
    cout << "result" << result << endl;
    cout << "hash" << hash << endl;

    str1[k-i-1] = result + '0';
  }
  cout << str1.at(0) << str1.at(1) << str1.at(2) << "Str" << endl;

  for (i = 1 ; i <= 3 ; ++i) {
    printf("Computing for distance %d\n", i);
    magic(str1, k - 1, i);
  }
  printf("----------------\n");
  //cout << str[0] << str[1] << str[2] <<endl;
  /* Find the hamming distance and check into these buckets */

}

void Hypercube::magic(string& str, int i, int changesLeft) {
        if (changesLeft == 0) {
          cout << str << endl;
          return;
        }
        if (i < 0) return;
        // flip current bit
        str[i] = str[i] == '0' ? '1' : '0';
        magic(str, i-1, changesLeft-1);
        // or don't flip it (flip it again to undo)
        str[i] = str[i] == '0' ? '1' : '0';
        magic(str, i-1, changesLeft);
}

Hypercube::~Hypercube() {

}
