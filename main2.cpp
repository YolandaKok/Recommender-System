#include <iostream>
#include "Hypercube.h"
#include "IOutils.h"
#include "ExactKnn.h"
#include <fstream>
#include <cstring>
#include <string>
#include <random>

using namespace std;

random_device rd;
default_random_engine generator(rd());

int main(int argc, char* argv[]) {
  char *inputFile = NULL, *queryFile = NULL, *outputFile = NULL;
  int k, L, size;
  int M, probes;
  int i;
  double R = 0.0;
  char metric[10];
  string str2;
  strcpy(metric, "euclidean");

  srand(time(NULL));
  /* Read the input file */
  readArgs(argv, argc, inputFile, queryFile, k, L, outputFile, M, probes);
  /* Create the exact KNN algorithm */
  vector<Point*> input;
  input = readInput(inputFile, " ", "\n", k, size, 1, R, metric);

  Hypercube *hypercube = new Hypercube(input.size(), k, probes, M, metric);

  for(i = 0; i < input.size(); i++)
    hypercube->insert_point(input.at(i));

  vector<Point*> query;
  query = readInput(queryFile, " ", "\n", k, size, 0, R, metric);
  if(strncmp(metric, "euclidean", 9) == 0) {
      str2 = "euclidean";
  }

  if(strncmp(metric, "cosine", 6) == 0) {
      str2 = "cosine";
  }
  ofstream myfile;
  myfile.open(outputFile);
  //hypercube->points_per_bucket();

  for(i = 0; i < query.size(); i++)
    hypercube->findNearest(query.at(i), query.size(), myfile, R);
  myfile.close();
  cout << hypercube->structureSizeCube() / (1024 * 1024) << endl;
  delete hypercube;
    //cout << R << endl;
    cout << metric << endl;
  return 1;
}
