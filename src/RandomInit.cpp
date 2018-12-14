//
// Created by yolanda on 10/11/2018.
//

#include "RandomInit.h"
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

extern mt19937 gen;
extern default_random_engine generator;

using namespace std;
/* Select k random centroids for the clusters */
vector<Point*> RandomInit::findCentroids(vector<Point*> dataset, int clusters) {
    vector<Point*> centroids;
    int index, i;
    centroids.clear();
    uniform_int_distribution<> dis(0, dataset.size());
    vector<Point*>::iterator it;
    int count = 0;
    /* Select Random Centroids */
    while( count < clusters) {
        index = dis(generator);
        it = find (centroids.begin(), centroids.end(), dataset.at(index));
        if (it != centroids.end()) {

        }
        else {
            centroids.push_back(dataset.at(index));
            dataset.at(index)->setCentroid(true);
            dataset.at(index)->setInitialCentroid(true);
            count++;
        }
        //cout << index << endl;
    }
    return centroids;
}