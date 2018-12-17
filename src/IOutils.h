#ifndef __IOUTILS__
#define __IOUTILS__
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <unordered_map>
#include "Point.h"
#include "Tweet.h"
using namespace std;
/* Read input data */
vector<Point*> readInput(const char filename[], const char seperator[], const char delimiter[], int k, int& size, int input, double& R, char metric[10]);
/* Read the arguments */
int readArgs(char* argv[], int argc, char*& input_file, char*& queryFile, int& k, int& L, char*& outputFile, int& probes, int& M);
/* File input2 */
vector<Point*> readFile(const char filename[], int k, int& size, int input, double& R, string& metric, char separator);
/* Read Clusters conf file */
int readConf(const char filename[], int& k, int& L, int& clusters, int& probes, double& w);

map<string, vector<Tweet*>> readFileRecommend(const char filename[], int& size, int input, int& P, char separator);

void readDictionary(const char filename[], unordered_map<string, double>* dictionary, char separator);

#endif
