#include <iostream>
#include "Hypercube.h"
#include "IOutils.h"
#include <fstream>
#include <cstring>
#include <string>
#include <random>

using namespace std;

random_device rd;
default_random_engine generator(rd());

int main(int argc, char* argv[]) {
  char *inputFile = NULL, *queryFile = NULL, *outputFile = NULL;
  int k = 3, L, size;
  int M = 10, probes = 2;
  int i;
  double R = 0.0;
  string metric("euclidean");

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

  char inputF[100];
  char queryF[100];
  char outputF[100];
  if( inputFile == NULL ) {
    cout << "Insert input dataset path: " << endl;
    cin >> inputF ;
    inputFile = (char*)malloc(strlen(inputF) + 1);
    strcpy(inputFile, inputF);
  }

  srand(time(NULL));
  /* Read the input file */
  /* Create the exact KNN algorithm */
  vector<Point*> input;
  input = readFile(inputFile, k, size, 1, R, metric);
  Hypercube *hypercube;
  vector<Point*> query;
  string answer("yes");
  int count = 0;
  while(answer.compare("yes") == 0) {
    if( queryFile == NULL ) {
      cout << "Insert query path: " << endl;
      cin >> queryF ;
      queryFile = (char*)malloc(strlen(queryF) + 1);
      strcpy(queryFile, queryF);
    }


    query = readFile(queryFile, k, size, 0, R, metric);

    if(count == 0) {
      hypercube = new Hypercube(input.size(), input.at(0)->getDimension(), k, probes, M, metric);

      for(i = 0; i < input.size(); i++)
        hypercube->insert_point(input.at(i));
    }

    if( outputFile == NULL ) {
      cout << "Insert output path: " << endl;
      cin >> outputF ;
      outputFile = (char*)malloc(strlen(outputF) + 1);
      strcpy(outputFile, outputF);
    }


      ofstream myfile;
      myfile.open(outputFile);
      //hypercube->points_per_bucket();
      vector<Point*> nearest;
      vector<Point*> range_items;
      Point* nearest_neighbor;
      Point* exact;
      for(i = 0; i < query.size(); i++) {
        myfile << "Query: Item " << query.at(i)->getId() << endl;
        /* Find all the nearest in the probes */
        nearest = hypercube->findNearest(query.at(i));
        /* Find the nearest neighbor approximate */
        nearest_neighbor = hypercube->approximateNN(nearest, query.at(i));
        myfile << "Nearest Neighbor: " << nearest_neighbor->getId() << endl;
        myfile << "Nearest Neighbor distance: " << nearest_neighbor->euclidean(query.at(i)) << endl;
        /* Range Search */
        if(R > 0.0) {
          range_items = hypercube->rangeSearch(nearest, query.at(i), R);
        }
        myfile << "Range Items: " << endl;
        for( int j = 0; j < range_items.size(); j++ ) {
          myfile << range_items.at(j)->getId() << endl;
          myfile << range_items.at(j)->euclidean(query.at(i)) << endl;
        }
        exact = hypercube->exactNN(query.at(i));
        myfile << "Exact Neighbor distance: " << exact->euclidean(query.at(i)) << endl;
        myfile << "Exact NN: " << exact->getId() << endl;
        myfile << endl;
      }
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

  cout << "Hypercube Size: " << hypercube->structureSizeCube() << " bytes" << endl;
  delete hypercube;

  for(int i = 0; i < input.size(); i++) {
    delete input.at(i);
  }

  free(inputFile);


  return 1;
}
