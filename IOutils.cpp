#define LINE_SIZE 500
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <string>
#include <vector>
#include <list>
#include "IOutils.h"
#include "Point.h"
#include <stdlib.h>
#include <time.h>
#include "ExactKnn.h"
#include "H.h"
#include "F.h"

using namespace std;
/* Read the dataset file */
vector<Point*> readInput(const char filename[], const char seperator[], const char delimiter[], int k, int& size, int input, double& R) {
  /* Initialize random seed */
  srand (time(NULL));
  FILE *fp = NULL;
  char line[LINE_SIZE];
  char *name = NULL, *token = NULL, *delimiters = NULL;
  char *ptr = NULL;
  /* Array of points */
  vector<Point*> points;
  delimiters = (char*)malloc(strlen(seperator) + strlen(delimiter) + 1);
  strcat(delimiters, seperator);
  strcat(delimiters, delimiter);
  name = (char*)malloc(strlen(filename) + strlen("datasets/") + 1);
  sprintf(name, "datasets/%s", filename);
  /* Open the file */
  fp = fopen(name,"r");
  if(fp == NULL)
    assert(fp != NULL);

  /* Set the id for the point */
  int i = 0;
  int flag = 0;
  /* Read line by line */
  while (fgets(line, LINE_SIZE, fp)) {
    token = strtok(line, delimiters);
    cout << token << "token" << endl;
    if(!strcmp(token, "Radius:")) {
      token = strtok(NULL, delimiters);
      cout << token << endl;
      R = atof(token);
      flag = 1;
    }
    if(flag == 0) {
    /* Create a Point */
    Point *point = new Point();
    point->setId(i);
    while( token != NULL ) {
      //printf( "%s\n", token );
      /* Make token a double */
      /* Create an array of points */
      point->addCoord(atof(token));
      token = strtok(NULL, delimiters);
   }
   //point->print();
   i++;
   points.push_back(point);}
   flag = 0;
  }

  if(input)
    size = points.size();

  free(delimiters);
  free(name);
  return points;
}

/* Read the arguments */
int readArgs(char* argv[], int argc, char*& input_file, char*& queryFile, int& k, int& L, char*& outputFile) {
  int i;
  if(!strcmp(argv[0], "./lsh")) {
      //printf("lsh \n");
      /* Read the arguments for the lsh */
      /* Code to handle the command line flags */
      for(i = 1; i < argc; i += 2) {
        if(!strcmp(argv[i], "-d")) {
          input_file = (char*)malloc(strlen(argv[i+1]) + 1);
          strcpy(input_file, argv[i+1]);
        }
        else if(!strcmp(argv[i], "-q")) {
          queryFile = (char*)malloc(strlen(argv[i+1]) + 1);
          strcpy(queryFile, argv[i+1]);
          printf("%s\n", queryFile);
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
  }
}
