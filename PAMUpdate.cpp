//
// Created by yolanda on 15/11/2018.
//

#include "PAMUpdate.h"
#include <iostream>

using namespace std;

bool PAMUpdate::updateCentroids(vector<Point*>& dataset, vector<Point*>& centroids) {
    /* Find the clusters */
    /* Take the dimensions of a point */
    int dimension = dataset.at(0)->getDimension();
    vector<Point*> old_centroids;
    old_centroids = centroids;

    /* Find the clusters */
    vector<vector<Point*>> clusters;
    clusters.resize(centroids.size());

    for(int z = 0; z < dataset.size(); z++) {
        if(dataset.at(z)->isCentroid() == 0) {
            clusters.at(dataset.at(z)->getCluster()).push_back(dataset.at(z));
        }
    }

    for(int i = 0; i < centroids.size(); i++) {
        clusters.at(i).push_back(centroids.at(i));
    }

    vector<double> distances;
    double total_distance = 0.0;
    /* For every cluster use PAM */
    for( int i = 0; i < centroids.size(); i++ ) {
        /* For every object in the cluster */
        for( int j = 0; j < clusters.at(i).size(); j++ ) {
            /* Find the distances of this item to every other object in the cluster */
            //distances.resize(clusters.at(i).size());
            for(int k = 0; k < clusters.at(i).size(); k++) {
                /* Calculate euclidean squared distance */
                total_distance += clusters.at(i).at(j)->euclidean_squared(clusters.at(i).at(k));
            }
            distances.push_back(total_distance);
            total_distance = 0.0;
        }
        /* Make the previous centroid a non centroid point */
        centroids.at(i)->setCentroid(false);
        /* Find the minimum distance and the index */
        centroids.at(i) = clusters.at(i).at(minimum_index(distances));
        centroids.at(i)->setCentroid(true);
        distances.clear();
    }

    /* Check if any of the centroids have changed */
    /* Find if old centroids are differrent from the new */
    int count = 0;
    for(int i = 0; i < centroids.size(); i++) {
        if(centroids.at(i)->equalCoords(old_centroids.at(i))) {
            count++;
        }
    }

    if(count == centroids.size()) {
        return true;
    }
    else {
        return false;
    }

}


int PAMUpdate::minimum_index(vector<double> elements) {
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

int PAMUpdate::findSecondMinimum(vector<double> elements) {
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