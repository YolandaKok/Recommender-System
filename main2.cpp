#include <iostream>
#include "Hypercube.h"
#include "IOutils.h"
#include "ExactKnn.h"
#include <fstream>
#include <cstring>
#include <string>
#include <random>
#include "read.h"

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
  //string metric("euclidean");
  strcpy(metric, "euclidean");
  string str2;

  for(int i = 1; i < argc; i += 2) {
    if(!strcmp(argv[i], "-d")) {
      inputFile = (char*)malloc(strlen(argv[i+1]) + 1);
      strcpy(inputFile, argv[i+1]);
    }
    else if(!strcmp(argv[i], "-q")) {
      queryFile = (char*)malloc(strlen(argv[i+1]) + 1);
      strcpy(queryFile, argv[i+1]);
    }
    else if(!strcmp(argv[i], "-k")) {
      k = atoi(argv[i+1]);
    }
    else if(!strcmp(argv[i], "-L")) {
      L = atoi(argv[i+1]);
    }
    else if(!strcmp(argv[i], "-o")) {
      outputFile = (char*)malloc(strlen(argv[i+1]) + 1);
      strcpy(outputFile, argv[i+1]);
    }
    else if(!strcmp(argv[i], "-probes")) {
      probes = atoi(argv[i+1]);
    }
    else if(!strcmp(argv[i], "-M")) {
      M = atoi(argv[i+1]);
    }
  }

  srand(time(NULL));
  /* Read the input file */
  //readArgs(argv, argc, inputFile, queryFile, k, L, outputFile, M, probes);
  cout << inputFile << endl;
  /* Create the exact KNN algorithm */
  vector<Point*> input;
  input = readInput(inputFile, " ", "\n", k, size, 1, R, metric);
  //input = readFile(inputFile, R);

  vector<Point*> query;
  query = readInput(queryFile, " ", "\n", k, size, 0, R, metric);
  //query = readFile(queryFile, R);


    if(strncmp(metric, "euclidean", 9) == 0) {
        str2 = "euclidean";
    }

    if(strncmp(metric, "cosine", 6) == 0) {
        str2 = "cosine";
    }

  Hypercube *hypercube = new Hypercube(input.size(), k, probes, M, str2);

  for(i = 0; i < input.size(); i++)
    hypercube->insert_point(input.at(i));


  ofstream myfile;
  myfile.open(outputFile);
  //hypercube->points_per_bucket();
  for(i = 0; i < query.size(); i++)
    hypercube->findNearest(query.at(i), query.size(), myfile, R);
  myfile.close();
  //cout << hypercube->structureSizeCube() / (1024 * 1024) << endl;
  delete hypercube;
  return 1;
}
