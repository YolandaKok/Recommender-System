//
// Created by yolanda on 10/11/2018.
//

#include "LloydsAssign.h"
#include <iostream>

using namespace std;

// Assignment step
void LloydsAssign::assignCentroids(vector<Point*>& dataset, vector<Point*> centroids) {
    vector<double> distances_from_centroids;
    int index;
    // Find the nearest centroid
    for( int i = 0; i < dataset.size(); i++ ) {
        for( int j = 0; j < centroids.size(); j++ ) {
            if(dataset.at(i)->isCentroid() == 0) {
                /* Calculate distance for every centroid and find minimum */
                distances_from_centroids.push_back(dataset.at(i)->euclidean(centroids.at(j)));
                // TODO: also for cosine distance
            }
        }
        if(dataset.at(i)->isCentroid() == 0) {
            /* Find minimum */
            index = minimum_index(distances_from_centroids);
            //cout << index << endl;
            /* Assign to centroid */
            dataset.at(i)->setCluster(index);
        }
        distances_from_centroids.clear();
    }
    /* Now for every point i know in which cluster it belongs */
}

int LloydsAssign::minimum_index(vector<double> elements) {
    int index = 0;
    double min = elements.at(0);
    int i;
    for( i = 1; i < elements.size(); i++ ) {
        if(min > elements.at(i)) {
            min = elements.at(i);
            index = i;
        }
    }
    return index;
}