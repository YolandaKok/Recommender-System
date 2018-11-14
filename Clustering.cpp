#include <iostream>
#include <random>
#include "Clustering.h"
#include "KmeansppInit.h"
#include "RandomInit.h"
#include "LloydsAssign.h"
#include "KmeansUpdate.h"
#include "LshAssign.h"
#include "Lsh.h"
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;

extern default_random_engine generator;

Clustering::Clustering(int num_clusters, vector<Point*> dataset, string init, string assign, string update, int k, int L, string metric, int size) {
    this->num_clusters = num_clusters;
    this->dataset = dataset;
    if(!init.compare("random_selection")) {
        this->initialization = new RandomInit();
    }
    else {
        this->initialization = new KmeansppInit();
    }

    if(!assign.compare("Lloyds")) {
        this->assignment = new LloydsAssign();
    }
    else if(!assign.compare("RangeLSH")) {
        LSH *lsh = new LSH(L, size, k, dataset, metric, dataset.size(), dataset.at(0)->getDimension());
        this->assignment = new LshAssign(lsh);
    }

    if(!update.compare("k-means")) {
        this->update = new KmeansUpdate();
    }

    this->centroids = initialization->findCentroids(this->dataset, this->num_clusters);
    //this->assignment->assignCentroids(this->dataset, this->centroids);
}

/* Clustering until the centers are the same */
void Clustering::findClusters() {
    int count = 0;
    this->assignment->assignCentroids(this->dataset, this->centroids);
    while(!this->update->updateCentroids(this->dataset, this->centroids)) {
        //this->update->updateCentroids(this->dataset, this->centroids);
        this->assignment->assignCentroids(this->dataset, this->centroids);
        count++;
    }
    cout << count << endl;
    cout << "silhouette" << endl;
    Silhouette();
}


void Clustering::Silhouette() {
    /* Calculate clusters */
    vector<vector<Point*>> clusters;
    clusters.resize(centroids.size());

    for(int z = 0; z < dataset.size(); z++) {
        if(dataset.at(z)->isCentroid() == 0) {
            //cout << dataset.at(z)->getCluster() << endl;
            clusters.at(dataset.at(z)->getCluster()).push_back(dataset.at(z));
        }
    }
    cout << clusters.at(0).size() << endl;
    cout << clusters.at(1).size() << endl;
    cout << clusters.at(2).size() << endl;
    cout << clusters.at(3).size() << endl;
    cout << clusters.at(4).size() << endl;
    //cout << clusters.at(5).size() << endl;

    /* For every point in a cluster calculate the distance from all the other points */
    /* Find the average */
    /* And the distance of this point to the second minimum cluster */
    /* average distance of sample i to the other samples of the cluster and the second best cluster */
    double averageIntra = 0.0, averageNearest = 0.0, averageNearest1 = 0.0, averageNearest2 = 0.0, averageNearest3 = 0.0, averageNearest4 = 0.0;
    int initCluster, secondCluster;
    double average = 0.0;
    for(int i = 0; i < clusters.at(0).size(); i++) {
        secondCluster = clusters.at(0).at(i)->getSecondBestCluster();
        for(int j = 0; j < clusters.at(0).size(); j++) {
            averageIntra += clusters.at(0).at(i)->euclidean_squared(clusters.at(0).at(j)) / clusters.at(0).size();
            //cout << clusters.at(0).at(i)->euclidean(clusters.at(0).at(j)) << endl;
        }
        for(int j = 0; j < clusters.at(1).size(); j++) {
            averageNearest1 += clusters.at(0).at(i)->euclidean_squared(clusters.at(1).at(j)) / clusters.at(1).size();
        }


        for(int j = 0; j < clusters.at(2).size(); j++) {
            averageNearest2 += clusters.at(0).at(i)->euclidean_squared(clusters.at(2).at(j)) / clusters.at(2).size();
            //cout << clusters.at(0).at(i)->euclidean_squared(clusters.at(2).at(j)) << endl;
        }

        for(int j = 0; j < clusters.at(3).size(); j++) {
            averageNearest3 += clusters.at(0).at(i)->euclidean_squared(clusters.at(3).at(j)) / clusters.at(3).size();
        }


        for(int j = 0; j < clusters.at(4).size(); j++) {
            averageNearest4 += clusters.at(0).at(i)->euclidean_squared(clusters.at(4).at(j)) / clusters.at(4).size();
        }

    }

    cout << (averageNearest1 - averageIntra) / max(averageNearest1, averageIntra) << endl;
    cout << (averageNearest2 - averageIntra) / max(averageNearest2, averageIntra) << endl;
    cout << (averageNearest3 - averageIntra) / max(averageNearest3, averageIntra) << endl;
    cout << (averageNearest4 - averageIntra) / max(averageNearest4, averageIntra) << endl;


    cout << clusters.at(1).size() << endl;
    cout << clusters.at(2).size() << endl;
    cout << clusters.at(3).size() << endl;
    cout << clusters.at(4).size() << endl;


    /*for( int i = 0; i < dataset.size(); i++ ) {

        initCluster = dataset.at(i)->getCluster();

        for(int j = 0; j < clusters.at(initCluster).size(); j++) {
            averageIntra += dataset.at(i)->euclidean(clusters.at(initCluster).at(j)) / clusters.at(initCluster).size();
        }

        secondCluster = dataset.at(i)->getSecondBestCluster();

        for(int j = 0; j < clusters.at(secondCluster).size(); j++) {

            averageNearest += dataset.at(i)->euclidean(clusters.at(secondCluster).at(j)) / clusters.at(secondCluster).size();
        }

        average += (averageNearest - averageIntra) / max(averageNearest, averageIntra);
        averageIntra = 0.0;
        averageNearest = 0.0;
    }
    cout << average / dataset.size() << endl;*/
}


Clustering::~Clustering() {
    delete this->initialization;
    delete this->assignment;
    delete this->update;
}