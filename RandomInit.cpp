//
// Created by yolanda on 10/11/2018.
//

#include "RandomInit.h"
#include <iostream>
#include <random>

extern mt19937 gen;
extern default_random_engine generator;

using namespace std;
/* Select k random centroids for the clusters */
vector<Point*> RandomInit::findCentroids(vector<Point*> dataset, int clusters) {
    vector<Point*> centroids;
    int index, i;
    centroids.clear();
    uniform_int_distribution<> dis(0, dataset.size());
    /* Select Random Centroids */
    for( i = 0; i < clusters; i++ ) {
        index = dis(generator);
        centroids.push_back(dataset.at(index));
        dataset.at(index)->setCentroid(true);
        dataset.at(index)->setInitialCentroid(true);
        //dataset.at(index)->setCluster(i);
        cout << index << endl;
    }
    return centroids;
}