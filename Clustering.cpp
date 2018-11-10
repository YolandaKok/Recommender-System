#include <iostream>
#include <random>
#include "Clustering.h"
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;

extern default_random_engine generator;

Clustering::Clustering(int num_clusters, vector<Point*> dataset) {
    this->num_clusters = num_clusters;
    this->dataset = dataset;
    //randomSelection();
}

/* INITIALIZATION ALGORITHMS */

/* Select k random centroids for the clusters */
void Clustering::randomSelection() {
    int index, i;
    centroids.clear();
    /* Select Random Centroids */
    for( i = 0; i < this->num_clusters; i++ ) {
        index = rand() % dataset.size();
        centroids.push_back(dataset.at(index));
    }
}


void Clustering::k_means_pp() {
    int i;
    string index;
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
    vector<double> cumsum;
    vector<double> distances;
    vector<double> min_distances;
    /* While we have not found all the centers */
    while(centroids.size() < this->num_clusters) {
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
                break;
            }
        }
        min_distances.clear();
        cumsum.clear();
    }
}

double Clustering::minimum(vector<double> elements) {
    double min = elements.at(0);
    int i;
    for( i = 1; i < elements.size(); i++ ) {
        if(min > elements.at(i))
            min = elements.at(i);
    }
    return min;
}

double Clustering::sum(vector<double> elements) {
    double sum = 0.0;
    for(int i = 0; i < elements.size(); i++) {
        sum += elements.at(i);
    }
    return sum;
}

Clustering::~Clustering() {
    
}