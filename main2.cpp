#include <iostream>
#include "Hypercube.h"
#include "IOutils.h"

using namespace std;

int main(int argc, char* argv[]) {
  Hypercube *hypercube = new Hypercube(11, 20, 100);
  char *inputFile = NULL, *queryFile = NULL, *outputFile = NULL;
  int k, L, size;
  int i;
  /* Read the input file */
  //readArgs(argv, argc, inputFile, queryFile, k, L, outputFile);
  /* Create the exact KNN algorithm */
  vector<Point*> input;
  input = readInput("input_small", " ", "\n", k, size, 1);

  for(i = 0; i < input.size(); i++)
    hypercube->insert_point(input.at(i));

  vector<Point*> query;
  query = readInput("query_small", " ", "\n", k, size, 0);

  hypercube->findNearest(query.at(0));

  delete hypercube;
  return 1;
}
