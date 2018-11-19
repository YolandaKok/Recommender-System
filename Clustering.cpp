#include <iostream>
#include <random>
#include "Clustering.h"
#include "KmeansppInit.h"
#include "RandomInit.h"
#include "LloydsAssign.h"
#include "KmeansUpdate.h"
#include "LshAssign.h"
#include "Lsh.h"
#include "Hypercube.h"
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
        //string metric = "cosine";
        LSH *lsh = new LSH(L, size, k, dataset, metric, dataset.size(), dataset.at(0)->getDimension());
        Hypercube *cube = new Hypercube(size, dataset.at(0)->getDimension(), k, 8, 3, metric);
        lsh->bucket();
        this->assignment = new LshAssign(lsh, cube);
    }

    if(!update.compare("k-means")) {
        this->update = new KmeansUpdate();
    }
    else if(!update.compare("PAM")) {
        this->update = new PAMUpdate();
    }

    this->centroids = initialization->findCentroids(this->dataset, this->num_clusters);
    //this->assignment->assignCentroids(this->dataset, this->centroids);
}

/* Clustering until the centers are the same */
void Clustering::findClusters() {
    int count = 0;
    this->assignment->assignCentroids(this->dataset, this->centroids);
    while(!this->update->updateCentroids(this->dataset, this->centroids)) {
        this->assignment->assignCentroids(this->dataset, this->centroids);
        count++;
        if(count > 10) {
            break;
        }
    }
    //cout << count << endl;
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
    vector<double> second_distances;
    for( int k = 0; k < clusters.size(); k++ ) {
        for (int i = 0; i < clusters.at(k).size(); i++) {
            //secondCluster = clusters.at(k).at(i)->getSecondBestCluster();
            for(int z = 0; z < centroids.size(); z++) {
                second_distances.push_back(clusters.at(k).at(i)->euclidean_squared(centroids.at(z)));
            }
            secondCluster = findSecondMinimum(second_distances);
            for (int j = 0; j < clusters.at(k).size(); j++) {
                averageIntra += clusters.at(k).at(i)->euclidean_squared(clusters.at(k).at(j)) / clusters.at(k).size();
                //averageIntra += clusters.at(k).at(i)->getNearestDistance() / clusters.at(k).size();
            }
            for (int j = 0; j < clusters.at(secondCluster).size(); j++) {
                averageNearest1 += clusters.at(k).at(i)->euclidean_squared(clusters.at(secondCluster).at(j)) / clusters.at(secondCluster).size();
                //averageNearest1 += clusters.at(k).at(i)->getSecondNearestDistance() / clusters.at(secondCluster).size();
            }
            second_distances.clear();
        }
        cout << "Cluster " << k << " Silhouette" << endl;
        cout << (averageNearest1 - averageIntra) / max(averageNearest1, averageIntra) << endl;
        average += (averageNearest1 - averageIntra) / max(averageNearest1, averageIntra);
        averageIntra = 0.0;
        averageNearest1 = 0.0;
    }

    cout << "stotal " << average / clusters.size() << endl;
}


int Clustering::findSecondMinimum(vector<double> elements) {
    int index = 0, index2 = 0;
    double min = elements.at(0);
    int i;
    for( i = 1; i < elements.size(); i++ ) {
        if(min > elements.at(i)) {
            min = elements.at(i);
            index = i;
        }
    }

    double min2 = 1000.0;
    for( i = 0; i < elements.size(); i++ ) {
        if(i != index) {
            if(min2 > elements.at(i)) {
                min2 = elements.at(i);
                index2 = i;
            }
        }
    }

    return index2;
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