#include <iostream>
#include <random>
#include "Clustering.h"
#include "KmeansppInit.h"
#include "RandomInit.h"
#include "LloydsAssign.h"
#include "KmeansUpdate.h"
#include "LshAssign.h"
#include "Lsh.h"
#include "PAMUpdate.h"
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
    else if(!update.compare("PAM")) {
        this->update = new PAMUpdate();
    }

    this->centroids = initialization->findCentroids(this->dataset, this->num_clusters);
}

/* Clustering until the centers are the same */
void Clustering::findClusters() {
    int count = 0;
    this->assignment->assignCentroids(this->dataset, this->centroids);
    while(!this->update->updateCentroids(this->dataset, this->centroids)) {
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

    /* Array with average */

    /* For every point in a cluster calculate the distance from all the other points */
    /* Find the average */
    /* And the distance of this point to the second minimum cluster */
    /* average distance of sample i to the other samples of the cluster and the second best cluster */
    double averageIntra = 0.0, averageNearest = 0.0, averageNearest1 = 0.0, averageNearest2 = 0.0, averageNearest3 = 0.0, averageNearest4 = 0.0;
    int initCluster, secondCluster;
    double average = 0.0;
    for( int k = 0; k < clusters.size(); k++ ) {
        for (int i = 0; i < clusters.at(k).size(); i++) {
            secondCluster = clusters.at(k).at(i)->getSecondBestCluster();
            for (int j = 0; j < clusters.at(k).size(); j++) {
                averageIntra += clusters.at(k).at(i)->euclidean_squared(clusters.at(k).at(j)) / clusters.at(k).size();
            }
            for (int j = 0; j < clusters.at(secondCluster).size(); j++) {
                averageNearest1 += clusters.at(k).at(i)->euclidean_squared(clusters.at(secondCluster).at(j)) / clusters.at(secondCluster).size();
            }
        }
        cout << "Cluster " << k << " Silhouette" << endl;
        cout << (averageNearest1 - averageIntra) / max(averageNearest1, averageIntra) << endl;
        average += (averageNearest1 - averageIntra) / max(averageNearest1, averageIntra);
        averageIntra = 0.0;
        averageNearest1 = 0.0;
    }

    cout << "stotal " << average / clusters.size() << endl;
}

void Clustering::reinitialize() {
    for(int i = 0; i < dataset.size(); i++) {
        dataset.at(i)->setCentroid(false);
        dataset.at(i)->setInitialCentroid(false);
    }
}


Clustering::~Clustering() {
    delete this->initialization;
    delete this->assignment;
    delete this->update;
}