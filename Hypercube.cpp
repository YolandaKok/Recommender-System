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
  vector<tuple<int,double>> results, results2, ab;
  results = find(bucket_number, query, count_M, M);
  //cout << get<0>(results.at()) << "xoxo" << endl;
  //cout << count_M << endl;
  // Look at the first probe
  probes_count++;
  int count = 1;
  vector<string> strs;
  do {
    if(count_M == M)
      break;
    strs.clear();
    magic(str1, k - 1, count, strs);
    for(int j = 0; j < strs.size(); j++) {
      probes_count++;
      /* Found the bucket number */
      bucket_number = stoi(strs.at(j), nullptr, 2);
      results2 = find(bucket_number, query, count_M, M);
      for(int i = 0; i < results2.size(); i++) {
        results.push_back(results2.at(i));
      }
      /* Find the M points */
      //find(bucket_number, query, count_M, M);
      if(probes_count > this->probes)
        break;
      //cout << strs.at(j) << " " << "lala";
    }
    count++;
  } while(this->probes >= probes_count);

  for(int i = 0; i < results.size(); i++)
    cout << get<0>(results.at(i)) << "size" << results.size() << endl;
  /* Find the smallest distance */
  smallestDistance(results);
  /* Find with nn the smallest distance */
  /* Write it to a file */
}

tuple<int, double, double> Hypercube::smallestDistance(vector<tuple<int,double>>& input) {
  int id = get<0>(input.at(0));
  double distance = get<1>(input.at(0)), final_distance;
  for(int i = 1; i < input.size(); i++) {
    final_distance = get<1>(input.at(i));
    if(final_distance < distance) {
      id = get<0>(input.at(i));
      distance = final_distance;
    }
  }
  cout << distance << "distance" << endl;
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
