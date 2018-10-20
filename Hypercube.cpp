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
  int result, i, bucket_number;
  char z;
  char *str = (char*)malloc(k);
  int count_M = 0, probes_count = 0;
  string str1;
  str1.resize(k);
  for(i = 0; i < k; i++) {
    result = hash % 2;
    hash = hash / 2;
    /* Calculate the input string */
    str1[k-i-1] = result + '0';
  }
  cout << str1 << " str1" << endl;
  // Call the nearest neighbor function
  bucket_number = stoi(str1, nullptr, 2);
  count_M++;
  // Look at the first probe
  probes_count++;
  int count = 1;
  vector<string> strs;
  do {
    strs.clear();
    magic(str1, k - 1, count, strs);
    for(int j = 0; j < strs.size(); j++) {
      probes_count++;
      /* Found the bucket number */
      bucket_number = stoi(strs.at(j), nullptr, 2);
      
      if(probes_count > this->probes)
        break;
      cout << strs.at(j) << " " << "lala";
    }
    count++;
  } while(this->probes >= probes_count);

  /*for (i = 0 ; i < this->probes; ++i) {
    if(this->M > count_M) {

    }
    strs.clear();
    printf("Computing for distance %d\n", i + 1);
    magic(str1, k - 1, i + 1, strs);
    number = stoi(str1, nullptr, 2);
    count_M++;
  }
  printf("----------------\n");
  */
  //cout << strs.at(0) << endl; //" " << strs.at(1) << " " << strs.at(2) << " " << endl;
  /* Find the hamming distance and check into these buckets */
}

/* Find Nearest Neighbor into the bucket */


vector<string>& Hypercube::magic(string& str, int i, int changesLeft, vector<string>& strs) {
        if (changesLeft == 0) {
          cout << str << endl;
          strs.push_back(str);
          /* Hypercube */
          return strs;
        }
        if (i < 0) return strs;
        // flip current bit
        str[i] = str[i] == '0' ? '1' : '0';
        magic(str, i-1, changesLeft-1, strs);
        // or don't flip it (flip it again to undo)
        str[i] = str[i] == '0' ? '1' : '0';
        magic(str, i-1, changesLeft, strs);
}

Hypercube::~Hypercube() {

}
