#ifndef __IOUTILS__
#define __IOUTILS__
#include <cstdio>
#include <cstdlib>

/* Read input data */
int readInput(const char filename[], const char seperator[], const char delimiter[]);
/* Read the arguments */
int readArgs(char* argv[], int argc, char*& input_file, char*& queryFile, int& k, int& L, char*& outputFile);

#endif
