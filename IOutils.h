#ifndef __IOUTILS__
#define __IOUTILS__
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "Point.h"
using namespace std;
/* Read input data */
vector<Point*> readInput(const char filename[], const char seperator[], const char delimiter[], int k, int& size, int input, double& R, char metric[10]);
/* Read the arguments */
int readArgs(char* argv[], int argc, char*& input_file, char*& queryFile, int& k, int& L, char*& outputFile, int& probes, int& M);

#endif
