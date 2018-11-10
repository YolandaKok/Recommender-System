//
// Created by yolanda on 10/11/2018.
//

#include "RandomInit.h"

/* Select k random centroids for the clusters */
vector<Point*> RandomInit::findCentroids(vector<Point*> dataset, int clusters) {
    vector<Point*> centroids;
    int index, i;
    centroids.clear();
    /* Select Random Centroids */
    for( i = 0; i < clusters; i++ ) {
        index = rand() % dataset.size();
        centroids.push_back(dataset.at(index));
        dataset.at(index)->setCentroid(true);
    }
    return centroids;
}