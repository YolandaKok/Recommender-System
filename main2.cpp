#include <iostream>
#include "Hypercube.h"
#include "IOutils.h"
#include "ExactKnn.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
  Hypercube *hypercube = new Hypercube(11, 20, 10);
  char *inputFile = NULL, *queryFile = NULL, *outputFile = NULL;
  int k, L, size;
  int i;
  double R = 0.0;
  /* Read the input file */
  //readArgs(argv, argc, inputFile, queryFile, k, L, outputFile);
  /* Create the exact KNN algorithm */
  vector<Point*> input;
  input = readInput("input_small", " ", "\n", k, size, 1, R);

  for(i = 0; i < input.size(); i++)
    hypercube->insert_point(input.at(i));

  vector<Point*> query;
  query = readInput("query_small", " ", "\n", k, size, 0, R);
  ofstream myfile;
  myfile.open("output.txt");

  for(i = 0; i < query.size(); i++)
    hypercube->findNearest(query.at(i), query.size());
  //ExactKNN(query.at(1), input, myfile);
  //hypercube->findNearest(query.at(1), query.size());
  myfile.close();
  delete hypercube;
  return 1;
}
