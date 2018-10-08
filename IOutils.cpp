#define LINE_SIZE 200

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include "IOutils.h"

/* Read the dataset file */
int readInput(const char filename[], const char seperator[], const char delimiter[]) {
  FILE *fp = NULL;
  char line[LINE_SIZE];
  char *name, *token, *delimiters;
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
    while( token != NULL ) {
      printf( "%s\n", token );
      token = strtok(NULL, delimiters);
   }
  }

  free(delimiters);
  free(name);

  return true;
}
