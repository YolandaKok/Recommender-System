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
        cout << "POINT " << i << endl;
        for( int j = 0; j < centroids.size(); j++ ) {
            if(dataset.at(i)->isCentroid() == 0) {
                /* Calculate distance for every centroid and find minimum */
                distances_from_centroids.push_back(dataset.at(i)->cosine(centroids.at(j)));
                cout << dataset.at(i)->cosine(centroids.at(j)) << endl;
                // TODO: also for cosine distance
            }
        }
        if(dataset.at(i)->isCentroid() == 0) {
            /* Find minimum */
            index = minimum_index(distances_from_centroids);
            cout << "MINIMUM " << index << endl;
            /* Assign to centroid */
            dataset.at(i)->setCluster(index);
            /* Find the second best centroid */
            if(distances_from_centroids.size() != 1) {
                int second = findSecondMinimum(distances_from_centroids);
                dataset.at(i)->setSecondBestCluster(second);
                cout << "SECOND MIN " << second << endl;
                //cout << findSecondMinimum(distances_from_centroids) << endl;
            }
        }
        distances_from_centroids.clear();
    }
    /* Now for every point i know in which cluster it belongs */
}

/* Find the index for first and second minimum distance */

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

int LloydsAssign::findSecondMinimum(vector<double> elements) {
    int index = 0, index2 = 0;
    double min = elements.at(0);
    int i;
    for( i = 1; i < elements.size(); i++ ) {
        if(min > elements.at(i)) {
            min = elements.at(i);
            index = i;
        }
    }

    double min2 = 1000.0;
    for( i = 0; i < elements.size(); i++ ) {
        if(i != index) {
            if(min2 > elements.at(i)) {
                min2 = elements.at(i);
                index2 = i;
            }
        }
    }

    return index2;
}