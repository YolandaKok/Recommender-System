#define LINE_SIZE 200
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <string>
#include "IOutils.h"
#include "Point.h"
#include <stdlib.h>

using namespace std;
/* Read the dataset file */
int readInput(const char filename[], const char seperator[], const char delimiter[]) {
  FILE *fp = NULL;
  char line[LINE_SIZE];
  char *name, *token, *delimiters;
  int i;
  char *ptr;
  delimiters = (char*)malloc(strlen(seperator) + strlen(delimiter) + 1);
  strcat(delimiters, seperator);
  strcat(delimiters, delimiter);
  name = (char*)malloc(strlen(filename) + strlen("datasets/") + 1);
  sprintf(name, "datasets/%s", filename);
  /* Open the file */
  fp = fopen(name,"r");
  if(fp == NULL)
    assert(fp != NULL);

  /* Read line by line */
  while (fgets(line, LINE_SIZE, fp)) {
    token = strtok(line, delimiters);
    /* Create a Point */
    i = 0;
    Point *point = new Point();
    while( token != NULL ) {
      //printf( "%s\n", token );
      /* Make token a double */
      /* Create an array of points */
      if (i) {
        point->addCoord(strtod(token, &ptr));
      }
      else {
        point->setId();
      }

      token = strtok(NULL, delimiters);
      i++;
   }
   i = 0;
   point->print();
  }

  free(delimiters);
  free(name);

  return true;
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
