#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <random>
#include "IOutils.h"
#include "Hashtable.h"
#include "F.h"
#include "Lsh.h"
#include <fstream>
#include <string>
#include <cstring>
#include <stdexcept>

random_device rd;
default_random_engine generator(rd());

int main(int argc, char* argv[]) {
  char *inputFile = NULL, *queryFile = NULL, *outputFile = NULL;
  int k = 4, L = 5, size;
  double R = 0.0;
  char metric[10];
  strcpy(metric, "euclidean");
  srand(time(NULL));
  string str2;
  /* Read the input file */
  //readArgs(argv, argc, inputFile, queryFile, k, L, outputFile, M, probes);

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

  /* Create the exact KNN algorithm */
  vector<Point*> input;
  input = readInput(inputFile, " ", "\n", k, size, 1, R, metric);

  //cout << input.at(0)->getDimension() << endl;
  vector<Point*> query;
  //query = readInput(queryFile, " ", "\n", k, size, 0, R, metric);
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


    query = readInput(queryFile, " ", "\n", k, size, 0, R, metric);

    if(strncmp(metric, "euclidean", 9) == 0) {
        str2 = "euclidean";
    }

    if(strncmp(metric, "cosine", 6) == 0) {
        str2 = "cosine";
    }
    if(count == 0) {
      lsh = new LSH(L, size, k, input, str2, input.size(), input.at(0)->getDimension());
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
      /* Deallocate query */
      for(int i = 0; i < query.size(); i++) {
        delete query.at(i);
      }
  }

  cout << "Used: " << lsh->structureSize() << " bytes" << endl;
  delete lsh;

  for(int i = 0; i < input.size(); i++) {
    delete input.at(i);
  }

  free(inputFile);

  return 1;
}
