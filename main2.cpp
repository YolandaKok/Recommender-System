#include <iostream>
#include "Hypercube.h"
#include "IOutils.h"
#include "ExactKnn.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
  Hypercube *hypercube = new Hypercube(11, 40, 10);
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
  ofstream myfile;
  myfile.open("output.txt");
  ExactKNN(query.at(1), input, myfile);
  hypercube->findNearest(query.at(1));
  myfile.close();
  delete hypercube;
  return 1;
}
