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
            /* Assign to centroid */
            dataset.at(i)->setCluster(index);
            /* Find the second best centroid */
            if(distances_from_centroids.size() != 1) {
                dataset.at(i)->setSecondBestCluster(findSecondMinimum(distances_from_centroids));
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
    int indexFirst = 0, indexSecond = 1;
    double smallest = elements.at(0), second = elements.at(1), temp;
    if(second < smallest) {
        temp = smallest;
        smallest = second;
        second = temp;
    }
    for( int i = 2; i < elements.size(); i++ ) {
        if(elements.at(i) < smallest) {
            second = smallest;
            smallest = elements.at(i);
            indexFirst = i;
        }
        else {
            if(elements.at(i) < second) {
                second = elements.at(i);
                indexSecond = i;
            }
        }
    }

    vector<int> indexes;
    indexes.push_back(indexFirst);
    indexes.push_back(indexSecond);

    return indexes.at(1);
}