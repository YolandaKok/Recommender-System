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
    char *inputFile = NULL, *confFile = NULL, *outputFile = NULL, *separator = NULL;
    srand(time(NULL));
    //string separator;
    char sep = ',';
    /* k - number of hash functions */
    /* L number of hashtables */
    int k = 4, L = 5, size, clusters = 5, probes = 5;
    double R = 0.0, w = 3.0;
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
        else if(!strcmp(argv[i], "-separator")) {
            separator = (char*)malloc(strlen(argv[i+1]) + 1);
            strcpy(separator, argv[i+1]);
            //separator = argv[i + 1];
            if(!strcmp(separator, "tab")) {
                sep = '\t';
            }
            else {
                sep = ',';
            }
        }
    }

    /* Read Configuration File */
    readConf(confFile, k, L, clusters, probes, w);
    /* Read Input file */
    vector<Point*> input;
    input = readFile(inputFile, k, size, 1, R, metric, sep);

    vector<string> initialization = {"random_selection", "k-means++"};
    vector<string> assignment = {"Lloyds", "RangeLSH", "RangeHypercube"};
    vector<string> update = {"k-means", "PAM"};

    ofstream myfile;
    myfile.open(outputFile);
    Clustering *clustering;
    for( int i = 0; i < initialization.size(); i++ ) {
        for(int j = 0; j < assignment.size(); j++) {
            for(int z = 0; z < update.size(); z++) {
                clustering = new Clustering(clusters, input, initialization.at(i), assignment.at(j), update.at(z), k, L, metric, size, probes, w);
                clustering->findClusters();
                vector<double> si = clustering->Silhouette();
                clustering->print(si, outputFile, myfile, false);
                clustering->reinitialize();
                delete clustering;
            }
        }
    }

    /* Run it for more multiple combinations of clusters */

    /*vector<int> cluster = {5, 10, 20, 50, 100, 200, 250, 300, 500};

    for(int i = 0; i < cluster.size(); i++) {
        clustering = new Clustering(cluster.at(i), input, initialization.at(0), assignment.at(1), update.at(0), k, L, metric, size, probes, w);
        clustering->findClusters();
        vector<double> si = clustering->Silhouette();
        clustering->print(si, outputFile, myfile);
        clustering->reinitialize();
        delete clustering;
    }*/


    /*clustering = new Clustering(clusters, input, initialization.at(0), assignment.at(1), update.at(0), k, L, metric, size, probes, w);
    clustering->findClusters();
    vector<double> si = clustering->Silhouette();
    clustering->print(si, outputFile, myfile);
    clustering->reinitialize();

    delete clustering;*/

    myfile.close();

    /* Deallocate input */
    for(int i = 0; i < input.size(); i++) {
        delete input.at(i);
    }

    free(inputFile); free(confFile); free(outputFile);
    return 1;
}
