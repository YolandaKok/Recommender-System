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
#include <map>
#include <iterator>

using namespace std;

/* Constructor for the Hypercube */
Hypercube::Hypercube(int input_size, double dimension, int k, int probes, int M, string lsh_family):Hashtable(k, input_size, dimension, lsh_family) {
  this->probes = probes;
  this->M = M;
  this->lsh_family = lsh_family;
  this->dimension = dimension;
}

/* Value of h function */
int Hypercube::insert_point(Point *p) {
  map<int, int>::iterator it ;
  int value;
  vector<bool> bucket_number;
  vector<int> hash;
  int k = getK();
  /* Get all the h functions */
  hash = getHFunctions(p);
  for(int i = 0; i < getK(); i++) {
    it = this->hash_values.find(hash.at(i));
    /* Check if h value is not into the map */
    /* If it is not into the map find a random 0 or 1 */
    if(it == this->hash_values.end()) {
      value = rand() % 2;
      bucket_number.push_back(value);
      this->hash_values.insert(pair <int, int> (hash.at(i), value));
    }
    else {
        bucket_number.push_back(it->second);
    }
  }

  insert(p, toInt(bucket_number));
}

/* Convert a vector<bool> to int */
int Hypercube::toInt(vector<bool> boolean) {
  int decimal = 0;
  for(int i = 0; i < getK(); i++) {
    decimal += (int)pow(2.0, i) * boolean.at(getK()-i-1);
  }
  return decimal;
}

/* Return vector<bool> for getH from vector<int> */
int Hypercube::hashValue(vector<int> elements) {
  map<int, int>::iterator it;
  vector<bool> number;
  int final_number;

  for(int i = 0; i < getK(); i++) {
    it = this->hash_values.find(elements.at(i));

    if(it == this->hash_values.end()) {
      number.push_back(0);
    }
    else {
        number.push_back(it->second);
    }
  }
  return toInt(number);
}


void Hypercube::findNearest(Point *query, int size, ofstream& output, double R) {
  /* getHFunctions for query */
  vector<int> hash_array = getHFunctions(query);
  int hash = hashValue(hash_array);
  int k = getK();
  int result, i, bucket_number;
  char z;
  char *str = (char*)malloc(k);
  int count_M = 0, probes_count = 0;
  static int count_size = 0;
  double static mean_time_lsh = 0.0;
  double time_;
  count_size++;
  string str1;
  str1.resize(k);
  /* From string to int */
  for(i = 0; i < k; i++) {
    result = hash % 2;
    hash = hash / 2;
    /* Calculate the input string */
    str1[k-i-1] = result + '0';
  }
  output << "Query: Item " << query->getId() << endl;
  // Call the nearest neighbor function
  bucket_number = stoi(str1, nullptr, 2);
  //cout << str1 << endl;
  vector<tuple<string,double>> results, results2, ab;
  /* Start Counting Time */
  results = find(bucket_number, query, count_M, M);
  //cout << count_M << endl;
  // Look at the first probe
  clock_t begin_time = clock();
  probes_count++;
  int count = 1;
  vector<string> strs;
  do {
    /*if(count_M == M)
      break;*/
    strs.clear();
    hamming(str1, k - 1, count, strs);
    for(int j = 0; j < strs.size(); j++) {
      probes_count++;
      if(probes_count > this->probes)
        break;
      /* Found the bucket number */
      bucket_number = stoi(strs.at(j), nullptr, 2);
      results2 = find(bucket_number, query, count_M, M);
      for(int i = 0; i < results2.size(); i++) {
        results.push_back(results2.at(i));
      }
      /* Find the M points */
      if(probes_count > this->probes)
        break;
      results2.clear();
    }
    count++;
  } while(this->probes >= probes_count);

  double smallest, nnDistance, max_approximation;
  static double final_max_approximation = 0.0;
  /* Find the smallest distance */
  smallest = smallestDistance(results, output);
  time_ = double( clock () - begin_time ) /  CLOCKS_PER_SEC;
  output << "tCube: " << time_ << endl;
  mean_time_lsh += time_;
  /* Find R nearest neighbors for query */
  if(R > 0.0) {
    output << "Range Items: " << endl;
    for(int z = 0; z < results.size(); z++) {
      if(get<1>(results.at(z)) < R) {
        output << "Item " << get<0>(results.at(z)) << endl;
      }
    }

  }
  /* Find the nearest neighbor */
  nnDistance = exactNN(query, output);
  max_approximation = smallest / nnDistance;
  /* Find with nn the smallest distance */
  if(max_approximation > final_max_approximation) {
    final_max_approximation = max_approximation;
  }
  if(count_size == size) {
      cout << "Max approximation: " << final_max_approximation << endl;
      cout << "tMean: " << mean_time_lsh/size << endl;
      count_size = 0;
      mean_time_lsh = 0.0;
      final_max_approximation = 0.0;
  }
  free(str);
}

double Hypercube::smallestDistance(vector<tuple<string,double>>& input, ofstream& output) {
  string id = get<0>(input.at(0));
  double distance = get<1>(input.at(0)), final_distance;
  for(int i = 1; i < input.size(); i++) {
    final_distance = get<1>(input.at(i));
    if(final_distance < distance) {
      id = get<0>(input.at(i));
      distance = final_distance;
    }
  }
  output << "Nearest Neighbor: " << id << endl;
  output << "distanceCube: " << distance << endl;
  return distance;
}

/* Find all the strings with hamming distance k */
vector<string>& Hypercube::hamming(string& str, int i, int changesLeft, vector<string>& strs) {
        if (changesLeft == 0) {
          strs.push_back(str);
          /* Hypercube */
          return strs;
        }
        if (i < 0) return strs;
        // flip current bit
        str[i] = str[i] == '0' ? '1' : '0';
        hamming(str, i-1, changesLeft-1, strs);
        // or don't flip it (flip it again to undo)
        str[i] = str[i] == '0' ? '1' : '0';
        hamming(str, i-1, changesLeft, strs);
}

/* Find the structure size */
int Hypercube::structureSizeCube() {
  //cout << "Points " << getPointsSize() << " bytes" << endl;
  return sizeof(class Hypercube) + structureSize() + sizeof(hash_values) + hash_values.size() * sizeof(int) * 2 + getPointsSize();
}

Hypercube::~Hypercube() {

}
