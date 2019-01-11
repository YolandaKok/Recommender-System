//
// Created by yolanda on 28/12/2018.
//

#include "ClusterRecommend.h"
#include "Clustering.h"
#include "Point.h"
#include "Rating.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

ClusterRecommend::ClusterRecommend(vector<Point*> dataset, int P, string init, string assign, string update, int k, int L,
        string metric, int size, int probes, double w) {
    // Number of the clusters
    // Size of the dataset and P neighbors
    this->total_time = clock();
    int num_clusters = size / P;
    //this->points = dataset;
    this->queries = dataset;
    // Create clustering instance
    this->clustering = new Clustering(num_clusters, dataset, init, assign, update, k, L, metric, size, probes, w);
    this->clustering->findClusters();
    this->clustering->Silhouette();
    this->clusters = this->clustering->getClusters();
}

/* Cluster Recommendation with different query set */


ClusterRecommend::ClusterRecommend(vector<Point*> dataset, int P, string init, string assign, string update, int k, int L,
                                   string metric, int size, int probes, double w, vector<Point*> query) {
    // Number of the clusters
    // Size of the dataset and P neighbors
    this->total_time = clock();
    int num_clusters = dataset.size() / P;
    this->points = dataset;
    this->queries = query;
    /* Concat the two vectors */
    this->points.insert(this->points.end(), this->queries.begin(), this->queries.end());
    // Create clustering instance
    this->clustering = new Clustering(num_clusters, this->points, init, assign, update, k, L, metric, this->points.size(), probes, w);
    this->clustering->findClusters();
    //this->clustering->Silhouette();
    this->clusters = this->clustering->getClusters();
}

vector<tuple<string, vector<string>>> ClusterRecommend::getRecommendations(vector<string>& coin_names, int num_of_coins) {
    vector<Point*> neighbors;
    vector<string> coins;
    vector<int> coins_indexes;
    map<string, int> which_cluster = this->clustering->getWhichCluster();
    for(int i = 0; i < this->queries.size(); i++) {
        this->queries.at(i)->subtractAverage();
    }
    for(int i = 0; i < this->queries.size(); i++) {
        // Find in which cluster is the user
        // Get all the items of this cluster
        // Calculate Rating
        //cout << which_cluster[this->points.at(i)->getId()] << endl;
        neighbors = this->clusters.at(which_cluster[this->queries.at(i)->getId()]);
        Rating *rating = new Rating(queries.at(i), neighbors, "euclidean");
        coins_indexes = rating->mainRating(num_of_coins);
        for(int j = 0; j < coins_indexes.size(); j++) {
            coins.push_back(coin_names.at(coins_indexes.at(j)));
        }
        this->coins_per_user.push_back(make_tuple(queries.at(i)->getId(), coins));
        coins.clear();
        delete rating;
    }
    this->total_time = double( clock () - this->total_time ) /  CLOCKS_PER_SEC;
    for(int i = 0; i < this->queries.size(); i++) {
        this->queries.at(i)->addAverage();
    }
    return this->coins_per_user;
}

void ClusterRecommend::print(string outputFile, string exercise, ofstream& myfile) {
    myfile << "Clustering" << endl;
    myfile << exercise << endl;
    for( int i = 0; i < this->coins_per_user.size(); i++ ) {
        myfile << "<u" << get<0>(coins_per_user.at(i)) << ">: ";
        vector<string> coins_recommendations = get<1>(coins_per_user.at(i));
        for(int j = 0; j < coins_recommendations.size(); j++) {
            myfile << coins_recommendations.at(j) << " ";
        }
        myfile << endl;
    }
    myfile << "Execution Time: " << this->total_time << "secs" << endl;
}

ClusterRecommend::~ClusterRecommend() {
    delete this->clustering;
}