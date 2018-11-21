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
#include <fstream>


using namespace std;

extern default_random_engine generator;

Clustering::Clustering(int num_clusters, vector<Point*> dataset, string init, string assign, string update, int k, int L, string metric, int size) {
    this->num_clusters = num_clusters;
    this->dataset = dataset;
    this->metric = metric;
    if(!init.compare("random_selection")) {
        this->initialization = new RandomInit();
        this->algorithms.push_back("Random Initialization");
    }
    else {
        this->initialization = new KmeansppInit();
        this->algorithms.push_back("K-means++");
    }

    if(!assign.compare("Lloyds")) {
        this->assignment = new LloydsAssign();
        this->algorithms.push_back("Lloyd's");
    }
    else if(!assign.compare("RangeLSH")) {
        //string metric = "cosine";
        LSH *lsh = new LSH(L, size, k, dataset, metric, dataset.size(), dataset.at(0)->getDimension());
        Hypercube *cube = new Hypercube(size, dataset.at(0)->getDimension(), k, 8, 3, metric);
        lsh->bucket();
        this->assignment = new LshAssign(lsh, cube);
        this->algorithms.push_back("Range Search with LSH");
    }

    if(!update.compare("k-means")) {
        this->update = new KmeansUpdate();
        this->algorithms.push_back("k-means");
    }
    else if(!update.compare("PAM")) {
        this->update = new PAMUpdate();
        this->algorithms.push_back("PAM");
    }
}

/* Clustering until the centers are the same */
void Clustering::findClusters() {
    clock_t begin_time = clock();
    int count = 0;
    this->centroids = initialization->findCentroids(this->dataset, this->num_clusters);
    this->assignment->assignCentroids(this->dataset, this->centroids);
    while(!this->update->updateCentroids(this->dataset, this->centroids)) {
        this->assignment->assignCentroids(this->dataset, this->centroids);
        count++;
        cout << count << endl;
        if(count > 17) {
            break;
        }
    }

    this->total_time = double( clock () - begin_time ) /  CLOCKS_PER_SEC;

    /* Create the clusters */
    this->clusters.resize(centroids.size());

    for(int z = 0; z < dataset.size(); z++) {
        if(dataset.at(z)->isCentroid() == 0) {
            //cout << dataset.at(z)->getCluster() << endl;
            clusters.at(dataset.at(z)->getCluster()).push_back(dataset.at(z));
        }
    }

    cout << "silhouette" << endl;
}

/* Get the data structure of clusters */
vector<vector<Point*>>& Clustering::getClusters() {
    return this->clusters;
}

void Clustering::print(vector<double> si, string output, ofstream& myfile) {
    myfile << "Algorithm: " << algorithms.at(0) << " " << algorithms.at(1) << " " << algorithms.at(2) << endl;
    myfile << "Metric: " << this->metric << endl;
    for( int i = 0; i < this->clusters.size(); i++ ) {
        myfile << "CLUSTER-" << i <<  "  { size:  " << clusters.at(i).size() << ", centroid:  ";
        if(!algorithms.at(2).compare("PAM")) {
            myfile << centroids.at(i)->getId();
        }
        else {
            centroids.at(i)->print(",", myfile);
        }
        myfile << endl;
    }
    myfile << "clustering time: " << this->total_time << " secs" << endl;
    myfile << "Silhouette: [";
    for( int i = 0; i < si.size() - 1; i++ ) {
        myfile << si.at(i) << ",";
    }
    myfile << si.at(si.size() - 1) << "]" << endl;

    myfile << endl;
    /* Count to break the line */
    int count = 0;
    /* Maybe you can choose what to print */
    /* Print the items of the clusters */
    for( int i = 0; i < clusters.size(); i++ ) {
        myfile << "CLUSTER-" << i << "  {";
        for( int j = 0; j < clusters.at(i).size(); j++ ) {
            myfile << clusters.at(i).at(j)->getId() << ", ";
            count++;
            if(count > 100) {
                myfile << endl;
                count = 0;
            }
        }
        myfile << "}" << endl;
        myfile << endl;
        count = 0;
    }
    myfile << endl;
}

vector<double> Clustering::Silhouette() {
    /* Calculate clusters */

    for(int i = 0; i < clusters.size(); i++) {
        cout << "SIZE of cluster " << i << endl;
        cout << clusters.at(i).size() << endl;
    }

    /* Array with average */

    /* For every point in a cluster calculate the distance from all the other points */
    /* Find the average */
    /* And the distance of this point to the second minimum cluster */
    /* average distance of sample i to the other samples of the cluster and the second best cluster */
    double averageIntra = 0.0, averageNearest = 0.0, averageNearest1 = 0.0;
    int initCluster, secondCluster;
    double average = 0.0;
    vector<double> second_distances;
    vector<double> si;
    double cluster_si;
    for( int k = 0; k < clusters.size(); k++ ) {
        for (int i = 0; i < clusters.at(k).size(); i++) {
            //secondCluster = clusters.at(k).at(i)->getSecondBestCluster();
            for(int z = 0; z < centroids.size(); z++) {
                second_distances.push_back(clusters.at(k).at(i)->euclidean(centroids.at(z)));
            }
            secondCluster = findSecondMinimum(second_distances);
            for (int j = 0; j < clusters.at(k).size(); j++) {
                averageIntra += clusters.at(k).at(i)->euclidean(clusters.at(k).at(j)) / clusters.at(k).size();
                //averageIntra += clusters.at(k).at(i)->getNearestDistance() / clusters.at(k).size();
            }
            for (int j = 0; j < clusters.at(secondCluster).size(); j++) {
                averageNearest1 += clusters.at(k).at(i)->euclidean(clusters.at(secondCluster).at(j)) / clusters.at(secondCluster).size();
                //averageNearest1 += clusters.at(k).at(i)->getSecondNearestDistance() / clusters.at(secondCluster).size();
            }
            second_distances.clear();
        }
        cout << "Cluster " << k << " Silhouette" << endl;
        cout << (averageNearest1 - averageIntra) / max(averageNearest1, averageIntra) << endl;
        cluster_si = (averageNearest1 - averageIntra) / max(averageNearest1, averageIntra);
        if( !isnan(cluster_si) ) {
            si.push_back((averageNearest1 - averageIntra) / max(averageNearest1, averageIntra) );
            average += (averageNearest1 - averageIntra) / max(averageNearest1, averageIntra);
        }
        else {
            si.push_back(0.0);
        }

        averageIntra = 0.0;
        averageNearest1 = 0.0;
    }

    si.push_back(average / clusters.size());
    cout << "stotal " << average / clusters.size() << endl;

    return si;
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
        dataset.at(i)->setR(0.0);
        dataset.at(i)->getClusters()->clear();
    }
    this->algorithms.clear();
    /* Remove items from the clusters */
    for( int i = 0; i < clusters.size(); i++ ) {
        clusters.at(i).clear();
    }
}


Clustering::~Clustering() {
    delete this->initialization;
    delete this->assignment;
    delete this->update;
}