//
// Created by yolanda on 10/11/2018.
//

#include "KmeansUpdate.h"

vector<Point*> KmeansUpdate::updateCentroids(vector<Point*> dataset, vector<Point*> centroids) {
    /* Take the dimensions of a point */
    int dimension = dataset.at(0)->getDimension();
    vector<Point*> newCentroids.resize(centroids.size());
    for(int i = 0; i < centroids.size(); i++) {
        newCentroids.at(i) = new Point();
        for (int j; j < dimension; j++) {
            newCentroids.at(i)->addCoord(0.0);
        }
    }
    // TODO: if it is not initial centroid deallocate the memory
    // TODO: create k sums

    for(int z = 0; z < dataset.size(); z++) {
        if(!dataset.at(z)->isCentroid()) {
            dataset.at(z)->getCluster();
        }
    }
    /* Find the new centroids */

}