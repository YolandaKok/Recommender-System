#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <random>
#include "IOutils.h"

int main(int argc, char* argv[]) {
  char *inputFile, *queryFile, *outputFile;
  int k, L;
  /* Read the input file */
  readInput("dataset.txt", "\t", "\n");
  readArgs(argv, argc, inputFile, queryFile, k, L, outputFile);
  printf("%s %s %s %d %d \n", inputFile, queryFile, outputFile, k, L);
  free(inputFile);free(queryFile);free(outputFile);
  return 1;
}
