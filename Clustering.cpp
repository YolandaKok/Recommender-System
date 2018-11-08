#include "Clustering.h"

Clustering::Clustering(int num_clusters, vector<Point*> dataset) {
    this->num_clusters = num_clusters;
    this->dataset = dataset;
    dataset.at(0)->print();
}

/* Select k random centroids for the clusters */
void Clustering::randomSelection() {
    //for(int i = 0; i < )
    // TODO: Select the random Centroids
    number = rand() % 10000;
}