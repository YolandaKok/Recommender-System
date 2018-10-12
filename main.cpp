#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <random>
#include "IOutils.h"
#include "Hashutils.h"

int main(int argc, char* argv[]) {
  char *inputFile = NULL, *queryFile = NULL, *outputFile = NULL;
  int k, L;
  /* Read the input file */
  readArgs(argv, argc, inputFile, queryFile, k, L, outputFile);
  /* Create the exact KNN algorithm */
  readInput(inputFile, " ", "\n", k);
  //printf("%s %s %s %d %d \n", inputFile, queryFile, outputFile, k, L);
  free(inputFile);free(queryFile);free(outputFile);
  return 1;
}
