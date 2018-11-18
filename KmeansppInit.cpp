//
// Created by yolanda on 10/11/2018.
//

#include "KmeansppInit.h"
#include <random>
#include <iostream>
#include <vector>
#include <algorithm>

extern mt19937 gen;

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
    //int initial_centroid = dis(gen);
    int initial_centroid = rand() % dataset.size();
    /* Removes the centroid from the dataset */
    remaining_elements.erase(remaining_elements.begin() + initial_centroid);
    //cout << initial_centroid << endl;
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
            if(dataset.at(i)->getInitialCentroid() == 0) {
                for( int j = 0; j < centroids.size(); j++ ) {
                    distances.push_back(dataset.at(i)->euclidean_squared(centroids.at(j)));
                }
                /* Find the minimum */
                min_distances.push_back(minimum(distances));
                distances.clear();
            }
        }
        cout << "Min distances " << min_distances.size() << endl;
        // Calculate the probability
        sum_distances = sum(min_distances);
        double max = maximum(min_distances);
        /* Normalize it */
        for( int z = 0; z < min_distances.size(); z++ ) {
            min_distances[z] /= sum_distances;
        }
        /* Find the cumulative sum */
        cumsum.resize(min_distances.size());

        partial_sum(min_distances.begin(), min_distances.end(), cumsum.begin(), plus<double>());
        cumsum.insert(cumsum.begin(), 0.0);
        double x = dist(gen);
        cout << x << "R" << endl;

        /* Find the first index that cumsum is >= r  */
        for(int r = 0; r < cumsum.size(); r++) {
            //TODO: binary search
            if(cumsum.at(r) >= x) {
                if(find(centroids.begin(), centroids.end(), dataset.at(r)) != centroids.end()) {
                    break;
                }
                else {
                    index = dataset.at(r)->getId();
                    cout << index << endl;
                    centroids.push_back(dataset.at(r));
                    dataset.at(r)->setCentroid(true);
                    dataset.at(r)->setInitialCentroid(true);
                    break;
                }
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

double KmeansppInit::maximum(vector<double> elements) {
    double max = elements.at(0);
    int i;
    for( i = 1; i < elements.size(); i++ ) {
        if(max < elements.at(i))
            max = elements.at(i);
    }
    return max;
}

double KmeansppInit::sum(vector<double> elements) {
    double sum = 0.0;
    for(int i = 0; i < elements.size(); i++) {
        sum += elements.at(i);
    }
    return sum;
}