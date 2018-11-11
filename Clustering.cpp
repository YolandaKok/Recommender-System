#include <iostream>
#include <random>
#include "Clustering.h"
#include "KmeansppInit.h"
#include "RandomInit.h"
#include "LloydsAssign.h"
#include "KmeansUpdate.h"
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;

extern default_random_engine generator;

Clustering::Clustering(int num_clusters, vector<Point*> dataset, string init, string assign, string update) {
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

    if(!update.compare("k-means")) {
        this->update = new KmeansUpdate();
    }

    this->centroids = initialization->findCentroids(this->dataset, this->num_clusters);
    /*for(int k = 0; k < this->centroids.size(); k++)
        cout << this->centroids.at(k)->getId() << " ";
    cout << endl;*/

    //LloydsAssign *loyds = new LloydsAssign();
    //loyds->assignCentroids(this->dataset, this->centroids);
    //KmeansUpdate *kmeansUpdate = new KmeansUpdate();
    //kmeansUpdate->updateCentroids(this->dataset, this->centroids);
    //delete loyds;
    //delete kmeansUpdate;

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

    vector<int> count1;
    count1.resize(this->centroids.size());
    for(int j = 0; j < count1.size(); j++) {
        count1.at(j) = 0;
    }
    for(int i = 0; i < this->dataset.size(); i++) {
        cout << this->dataset.at(i)->getCluster() << endl;
        count1.at(dataset.at(i)->getCluster()) += 1;
    }
    for(int j = 0; j < count1.size(); j++) {
        cout << count1.at(j) << endl;
    }

}




Clustering::~Clustering() {
    delete this->initialization;
    delete this->assignment;
    delete this->update;
}