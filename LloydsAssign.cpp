//
// Created by yolanda on 10/11/2018.
//

#include "LloydsAssign.h"
#include <iostream>

using namespace std;

LloydsAssign::LloydsAssign(string metric): Assignment(metric) {

}

// Assignment step
void LloydsAssign::assignCentroids(vector<Point*>& dataset, vector<Point*> centroids) {
    vector<double> distances_from_centroids;
    int index, second;
    // Find the nearest centroid
    for( int i = 0; i < dataset.size(); i++ ) {
        for( int j = 0; j < centroids.size(); j++ ) {
            if(dataset.at(i)->isCentroid() == 0) {
                /* Calculate distance for every centroid and find minimum */
                if(!metric.compare("euclidean")) {
                    distances_from_centroids.push_back(dataset.at(i)->euclidean(centroids.at(j)));
                }
                else if(!metric.compare("cosine")) {
                    distances_from_centroids.push_back(dataset.at(i)->cosine(centroids.at(j)));
                }

                // TODO: also for cosine distance
            }
        }
        if(dataset.at(i)->isCentroid() == 0) {
            /* Find minimum */
            index = minimum_index(distances_from_centroids);
            /* Assign to centroid */
            dataset.at(i)->setCluster(index);
            dataset.at(i)->setNearestDistance(distances_from_centroids.at(index));
            /* Find the second best centroid */
            if(distances_from_centroids.size() != 1) {
                second = findSecondMinimum(distances_from_centroids);
                dataset.at(i)->setSecondBestCluster(second);
                dataset.at(i)->setSecondNearestDistance(distances_from_centroids.at(second));
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