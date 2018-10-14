#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <random>
#include "IOutils.h"
#include "Hashutils.h"
#include "Hashtable.h"

int main(int argc, char* argv[]) {
  char *inputFile = NULL, *queryFile = NULL, *outputFile = NULL;
  int k, L, size;
  /* Read the input file */
  readArgs(argv, argc, inputFile, queryFile, k, L, outputFile);
  /* Create the exact KNN algorithm */
  vector<Point*> input;
  input = readInput(inputFile, " ", "\n", k, size, 1);

  vector<Point*> query;
  query = readInput(queryFile, " ", "\n", k, size, 0);

  Hashtable *hashtable = new Hashtable(size, query.at(0), k);

  free(inputFile);free(queryFile);free(outputFile);

  return 1;
}
