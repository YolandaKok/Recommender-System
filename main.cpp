#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <random>
#include "IOutils.h"
#include "Hashtable.h"
#include "F.h"
#include "ExactKnn.h"
#include "Lsh.h"
#include <fstream>
#include <string>
#include <cstring>

random_device rd;
default_random_engine generator(rd());

int main(int argc, char* argv[]) {
  char *inputFile = NULL, *queryFile = NULL, *outputFile = NULL;
  int k, L, size;
  double R = 0.0;
  char metric[10];
  strcpy(metric, "euclidean");
  srand(time(NULL));
  string str2;
  /* Read the input file */
  readArgs(argv, argc, inputFile, queryFile, k, L, outputFile);
  /* Create the exact KNN algorithm */
  vector<Point*> input;
  input = readInput(inputFile, " ", "\n", k, size, 1, R, metric);

  vector<Point*> query;
  query = readInput(queryFile, " ", "\n", k, size, 0, R, metric);

  ofstream myfile;
  myfile.open(outputFile);

  if(strncmp(metric, "euclidean", 9) == 0) {
      str2 = "euclidean";
  }

  if(strncmp(metric, "cosine", 6) == 0) {
      str2 = "cosine";
  }

  LSH *lsh = new LSH(L, size, k, input, str2);
  //lsh->bucket();
  for(int i = 0; i < query.size(); i++)
    lsh->find_nearest_neighbor(query.at(i), myfile, query.size(), R);

  cout << "Used: " << lsh->structureSize() / (1024 * 1024) << " MBs." << endl;
  delete lsh;
  myfile.close();

  for(int i = 0; i < query.size(); i++) {
    delete query.at(i);
  }

  for(int i = 0; i < input.size(); i++) {
    delete input.at(i);
  }

  free(inputFile);free(queryFile);free(outputFile);

  return 1;
}
