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
#include <tuple>
#include "Clustering.h"

using namespace std;

random_device rd;
mt19937 gen(rd());

default_random_engine generator(rd());

int main(int argc, char* argv[]) {
    char *inputFile = NULL, *confFile = NULL, *outputFile = NULL;
    srand(time(NULL));
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
    cout << k << endl;
    cout << L << endl;
    cout << clusters << endl;
    /* Read Input file */
    vector<Point*> input;
    input = readFile(inputFile, k, size, 1, R, metric);

    //input.at(1)->print();

    tuple<string, string> initialization("random_selection", "k-means++");
    tuple<string, string, string> assignment("Lloyds", "RangeLSH", "RangeHypercube");
    tuple<string, string> update("k-means", "PAM");

    Clustering *clustering = new Clustering(clusters, input, get<1>(initialization), get<0>(assignment), get<0>(update), k, L, metric, size);
    clustering->findClusters();

    /* Deallocate input */
    for(int i = 0; i < input.size(); i++) {
        delete input.at(i);
    }

    delete clustering;

    free(inputFile); free(confFile); free(outputFile);
    return 1;
}
