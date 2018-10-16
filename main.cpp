#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <random>
#include "IOutils.h"
#include "Hashtable.h"
#include "F.h"
#include "ExactKnn.h"
#include "Lsh.h"
#include <fstream>


int main(int argc, char* argv[]) {
  char *inputFile = NULL, *queryFile = NULL, *outputFile = NULL;
  int k, L, size;
  /* Read the input file */
  readArgs(argv, argc, inputFile, queryFile, k, L, outputFile);
  /* Create the exact KNN algorithm */
  vector<Point*> input;
  input = readInput(inputFile, " ", "\n", k, size, 1);

  vector<Point*> query;
  query = readInput(queryFile, " ", "\n", k, size, 0);

  ofstream myfile;
  myfile.open("output.txt");

  LSH *lsh = new LSH(L, size, k, input);
  lsh->find_nearest_neighbor(query.at(0), myfile, input);
  lsh->find_nearest_neighbor(query.at(1), myfile, input);
  lsh->find_nearest_neighbor(query.at(2), myfile, input);
  lsh->find_nearest_neighbor(query.at(3), myfile, input);

  //cout << query.at(29)->getId() << endl;
  delete lsh;
  myfile.close();
  //input.at(0)->print();

  Hashtable *hashtable = new Hashtable(size, k);
  for(int i = 0; i < input.size(); i++ ) {
    hashtable->insert(input.at(i));
  }

  //hashtable->traverse(152);
  hashtable->points_per_bucket();
  //cout << hashtable->hash_for_query(query.at(0)) << endl;
  //cout << query.at(0)->getDimension() << endl;
  //ExactKNN(query.at(0), input);
  //hashtable->find_nearest_neighbor(query.at(0));
  //F *f = new F(k);
  //Point* p = f->getV();
  //p->print();*/

  free(inputFile);free(queryFile);free(outputFile);

  return 1;
}
