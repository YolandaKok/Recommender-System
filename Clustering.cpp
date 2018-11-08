#include <iostream>
#include <random>
#include "Clustering.h"

using namespace std;

extern default_random_engine generator;

Clustering::Clustering(int num_clusters, vector<Point*> dataset) {
    this->num_clusters = num_clusters;
    this->dataset = dataset;
    randomSelection();
}

/* INITIALIZATION ALGORITHMS */

/* Select k random centroids for the clusters */
void Clustering::randomSelection() {
    int index, i;
    /* Select Random Centroids */
    for( i = 0; i < this->num_clusters; i++ ) {
        index = rand() % dataset.size();
        centroids.push_back(dataset.at(index));
    }
}


void Clustering::k_means_pp() {
    /* Choose a centroid uniformly at random */
    uniform_int_distribution<> dis(0, dataset.size() - 1);
    int initial_centroid = dis(generator);
    /* Put it into the centroids array */
    centroids.push_back(dataset.at(initial_centroid));
    /* Calculate the distance of the centroids to the remaining dataset */

}

Clustering::~Clustering() {
    
}