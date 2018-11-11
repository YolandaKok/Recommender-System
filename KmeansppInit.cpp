//
// Created by yolanda on 10/11/2018.
//

#include "KmeansppInit.h"
#include <random>
#include <iostream>

extern default_random_engine generator;

using namespace std;

KmeansppInit::KmeansppInit() {

}

vector<Point*> KmeansppInit::findCentroids(vector<Point*> dataset, int num_clusters) {
    int i;
    string index;
    vector<Point*> centroids;
    double sum_distances;
    // Copy dataset by assignment
    vector<Point*> remaining_elements;
    remaining_elements = dataset;
    /* Choose a centroid uniformly at random */
    uniform_int_distribution<> dis(0, dataset.size() - 1);
    uniform_real_distribution<> dist(0.0, 1.0);
    int initial_centroid = dis(generator);
    /* Removes the centroid from the dataset */
    remaining_elements.erase(remaining_elements.begin() + initial_centroid);
    cout << initial_centroid << endl;
    /* Put it into the centroids array */
    centroids.push_back(dataset.at(initial_centroid));
    dataset.at(initial_centroid)->setCentroid(true);
    dataset.at(initial_centroid)->setInitialCentroid(true);
    vector<double> cumsum;
    vector<double> distances;
    vector<double> min_distances;
    /* While we have not found all the centers */
    while(centroids.size() < num_clusters) {
        /* Calculate the distance of the centroids to the remaining dataset */
        /* min distance to some centroid, among t chosen centroids */
        for( i = 0; i < dataset.size(); i++ ) {
            for( int j = 0; j < centroids.size(); j++ ) {
                distances.push_back(dataset.at(i)->norm2(centroids.at(j)));
            }
            /* Find the minimum */
            min_distances.push_back(minimum(distances));
            //cout << minimum(distances) << endl;
            distances.clear();
        }
        // Calculate the probability
        sum_distances = sum(min_distances);
        cout << sum_distances<< endl;
        /* Normalize it */
        for( int z = 0; z < min_distances.size(); z++ ) {
            min_distances[z] /= sum_distances;
            //cout << min_distances[k] << endl;
        }
        /* Find the cumulative sum */
        cumsum.resize(min_distances.size());
        partial_sum(min_distances.begin(), min_distances.end(), cumsum.begin(), plus<double>());
        double x = dist(generator);
        cout << x << "R" << endl;
        /*for(int i = 0; i < cumsum.size(); i++) {
            cout << cumsum.at(i) << " ";
        }*/

        /* Find the first index that cumsum is >= r  */
        for(int r = 0; r < cumsum.size(); r++) {
            //TODO: binary search
            if(cumsum.at(r) >= x) {
                index = dataset.at(r)->getId();
                centroids.push_back(dataset.at(r));
                dataset.at(r)->setCentroid(true);
                dataset.at(r)->setInitialCentroid(true);
                break;
            }
        }
        min_distances.clear();
        cumsum.clear();
    }
    return centroids;
}

double KmeansppInit::minimum(vector<double> elements) {
    double min = elements.at(0);
    int i;
    for( i = 1; i < elements.size(); i++ ) {
        if(min > elements.at(i))
            min = elements.at(i);
    }
    return min;
}

double KmeansppInit::sum(vector<double> elements) {
    double sum = 0.0;
    for(int i = 0; i < elements.size(); i++) {
        sum += elements.at(i);
    }
    return sum;
}