#define LINE_SIZE 200

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include "IOutils.h"

/* Read the dataset file */
int readInput(const char filename[], char seperator, char delimiter) {
  FILE *fp = NULL;
  char line[LINE_SIZE];
  char *name;
  name = (char*)malloc(strlen(filename) + strlen("datasets/") + 1);
  sprintf(name, "datasets/%s", filename);
  /* Open the file */
  fp = fopen(name,"r");
  if(fp == NULL)
    assert(fp != NULL);

  while (fgets(line, LINE_SIZE, fp)) {
    printf("%s", line);
  }

  free(name);
}
