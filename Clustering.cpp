#include <iostream>
#include <random>
#include "Clustering.h"
#include "KmeansppInit.h"
#include "RandomInit.h"
#include "LloydsAssign.h"
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;

extern default_random_engine generator;

Clustering::Clustering(int num_clusters, vector<Point*> dataset, string init) {
    this->num_clusters = num_clusters;
    this->dataset = dataset;
    if(!init.compare("random_selection")) {
        this->initialization = new RandomInit();
    }
    else {
        this->initialization = new KmeansppInit();
    }
    this->centroids = initialization->findCentroids(this->dataset, this->num_clusters);
    for(int k = 0; k < this->centroids.size(); k++)
        cout << this->centroids.at(k)->getId() << " ";
    cout << endl;

    LloydsAssign *loyds = new LloydsAssign();
    loyds->assignCentroids(dataset, centroids);
    delete loyds;

}

/* INITIALIZATION ALGORITHMS */

Clustering::~Clustering() {
    
}