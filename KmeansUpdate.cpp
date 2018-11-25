#include "KmeansUpdate.h"
#include <iostream>
#include "Point.h"
#include "stdlib.h"

using namespace std;

bool KmeansUpdate::updateCentroids(vector<Point*>& dataset, vector<Point*>& centroids) {
    /* Take the dimensions of a point */
    int dimension = dataset.at(0)->getDimension();
    vector<Point*> old_centroids;
    old_centroids = centroids;
    // TODO: if it is not initial centroid deallocate the memory

    /*for(int i = 0; i < centroids.size(); i++) {
        if(centroids.at(i)->getInitialCentroid() == 0) {
            delete centroids.at(i);
        }
    }*/

    vector<vector<Point*>> clusters;
    clusters.resize(centroids.size());

    for(int z = 0; z < dataset.size(); z++) {
        if(dataset.at(z)->isCentroid() == 0) {
            //cout << dataset.at(z)->getCluster() << endl;
            clusters.at(dataset.at(z)->getCluster()).push_back(dataset.at(z));
        }
    }

    /* Find the new centroids */
    for(int i = 0; i < clusters.size(); i++) {
        //cout << "CLUSTER " << i << endl;
        Point *new_center = new Point();
        // initialize it with zeros
        initializePoint(dimension, new_center);
        for(int j = 0; j < clusters.at(i).size(); j++) {
            // Calculate the new centroid
            new_center->sumVectors(clusters.at(i).at(j));
        }
        new_center->divideVector(clusters.at(i).size());
        centroids.at(i) = new_center;
        centroids.at(i)->setCentroid(true);
        centroids.at(i)->setInitialCentroid(false);
    }

    /* Find if old centroids are differrent from the new */
    int count = 0;
    for(int i = 0; i < centroids.size(); i++) {
        if(centroids.at(i)->equalCoords(old_centroids.at(i))) {
            count++;
        }
    }

    cout << "Count" << count << endl;

    for(int i = 0; i < old_centroids.size(); i++) {
        if(old_centroids.at(i)->getInitialCentroid()) {
            old_centroids.at(i)->setInitialCentroid(false);
            old_centroids.at(i)->setCentroid(false);
        }
        else {
            delete old_centroids.at(i);
        }
    }

    //cout << "Count " << count << endl;

    if(count == centroids.size()) {
        return true;
    }
    else {
        return false;
    }
}

void KmeansUpdate::initializePoint(int dimension, Point* p) {
    for( int i = 0; i < dimension; i++ ) {
        p->addCoord(0.0);
    }
}