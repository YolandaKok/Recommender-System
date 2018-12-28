//
// Created by yolanda on 28/12/2018.
//

#include "ClusterRecommend.h"
#include "Clustering.h"
#include "Point.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

ClusterRecommend::ClusterRecommend(vector<Point*> dataset, int P, string init, string assign, string update, int k, int L,
        string metric, int size, int probes, double w) {
    // Number of the clusters
    // Size of the dataset and P neighbors
    int num_clusters = size / P;
    this->points = dataset;
    // Create clustering instance
    this->clustering = new Clustering(num_clusters, dataset, init, assign, update, k, L, metric, size, probes, w);
    this->clustering->findClusters();
    this->clustering->Silhouette();
    vector<vector<Point*>> clusters = this->clustering->getClusters();
    for( int i = 0; i < clusters.size(); i++ ) {
        cout << clusters.at(i).size() << endl;
    }
}

vector<tuple<string, vector<string>>> ClusterRecommend::getRecommendations(vector<string>& coin_names) {

}

ClusterRecommend::~ClusterRecommend() {
    delete this->clustering;
}