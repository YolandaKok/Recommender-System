#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <fstream>
#include <string>
#include <cstring>
#include <stdexcept>
#include <vector>
#include "Point.h"
#include "IOutils.h"
#include "Lsh.h"
using namespace std;

random_device rd;
default_random_engine generator(rd());

int main(int argc, char* argv[]) {
  char *inputFile = NULL, *queryFile = NULL, *outputFile = NULL;
  int k = 4, L = 5, size;
  double R = 0.0;
  //string str2;
  string metric("euclidean");
  srand(time(NULL));
  /* Read the arguments from the command line */
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
  }

  char inputF[100];
  char queryF[100];
  char outputF[100];
  if( inputFile == NULL ) {
    cout << "Insert input dataset path: " << endl;
    cin >> inputF ;
    inputFile = (char*)malloc(strlen(inputF) + 1);
    strcpy(inputFile, inputF);
  }

  /* Read Input file */
  vector<Point*> input;
  input = readFile(inputFile, k, size, 1, R, metric);
  cout << input.size() << endl;

  vector<Point*> query;
  string answer("yes");
  int count = 0;
  LSH *lsh;

  while(answer.compare("yes") == 0) {
    if( queryFile == NULL ) {
      cout << "Insert query path: " << endl;
      cin >> queryF ;
      queryFile = (char*)malloc(strlen(queryF) + 1);
      strcpy(queryFile, queryF);
    }

    query = readFile(queryFile, k, size, 0, R, metric);

    if(count == 0) {
      lsh = new LSH(L, size, k, input, metric, input.size(), input.at(0)->getDimension());
    }

    if( outputFile == NULL ) {
      cout << "Insert output path: " << endl;
      cin >> outputF ;
      outputFile = (char*)malloc(strlen(outputF) + 1);
      strcpy(outputFile, outputF);
    }


      ofstream myfile;
      myfile.open(outputFile);
      //lsh->bucket();
      for(int i = 0; i < query.size(); i++)
        lsh->find_nearest_neighbor(query.at(i), myfile, query.size(), R);
      myfile.close();
      cout << "Do you want to insert more query files ? (yes, no)" << endl;
      cout << endl;
      cin >> answer;
      free(outputFile);
      outputFile = NULL;
      free(queryFile);
      queryFile = NULL;
      count++;
      R = 0.0;
      /* Deallocate query */
      for(int i = 0; i < query.size(); i++) {
        delete query.at(i);
      }
  }

  cout << "Used: " << lsh->structureSize() << " bytes" << endl;
  delete lsh;

  /* Deallocate input */
  for(int i = 0; i < input.size(); i++) {
    delete input.at(i);
  }

  free(inputFile);
  return 1;
}
