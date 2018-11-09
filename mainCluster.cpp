#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <fstream>
#include <string>
#include <cstring>
#include <stdexcept>
#include <vector>
#include "Point.h"
#include "IOutils.h"
#include "Lsh.h"
#include "Clustering.h"

using namespace std;

random_device rd;
default_random_engine generator(rd());

int main(int argc, char* argv[]) {
    char *inputFile = NULL, *confFile = NULL, *outputFile = NULL;
    /* k - number of hash functions */
    /* L number of hashtables */
    int k = 4, L = 5, size, clusters = 0;
    double R = 0.0;
    string metric("euclidean");
    srand(time(NULL));
    /* Read the arguments from the command line */
    for(int i = 1; i < argc; i += 2) {
        /* Input File */
        if(!strcmp(argv[i], "-i")) {
            inputFile = (char*)malloc(strlen(argv[i+1]) + 1);
            strcpy(inputFile, argv[i+1]);
        }
        /* Configuration File */
        else if(!strcmp(argv[i], "-c")) {
            confFile = (char*)malloc(strlen(argv[i+1]) + 1);
            strcpy(confFile, argv[i+1]);
        }
        /* Metric */
        else if(!strcmp(argv[i], "-d")) {
            metric = argv[i + 1];
        }
        /* Output File */
        else if(!strcmp(argv[i], "-o")) {
            outputFile = (char*)malloc(strlen(argv[i+1]) + 1);
            strcpy(outputFile, argv[i+1]);
        }
    }

    /* Read Configuration File */
    readConf(confFile, k, L, clusters);
    /* Read Input file */
    vector<Point*> input;
    input = readFile(inputFile, k, size, 1, R, metric);

    // Create Clustering Class
    Clustering *clustering = new Clustering(clusters, input);
    clustering->k_means_pp();

    /* Deallocate input */
    for(int i = 0; i < input.size(); i++) {
        delete input.at(i);
    }

    delete clustering;

    free(inputFile); free(confFile); free(outputFile);
    return 1;
}
