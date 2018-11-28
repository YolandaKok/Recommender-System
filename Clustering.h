#ifndef LSH_CLUSTERING_H
#define LSH_CLUSTERING_H

#include "Point.h"
#include "Initialization.h"
#include "Assignment.h"
#include "Update.h"
#include "Hypercube.h"
#include "Lsh.h"
#include <fstream>

class Clustering {
    private:
        // Clusters Structure
        vector<vector<Point*>> clusters;
        // Num of clusters
        int num_clusters;
        double total_time;
        LSH *lsh;
        Hypercube *cube;
        // metric
        string metric;
        string output;
        string initName;
        string assignName;
        string updateName;
        // algorithms
        vector<string> algorithms;
        // Input Points
        vector<Point*> dataset;
        // Centroids
        vector<Point*> centroids;
        // Initialization
        Initialization *initialization;
        // Assignment
        Assignment *assignment;
        // Update
        Update *update;
    public:
        Clustering(int num_clusters, vector<Point*> dataset, string init, string assign, string update, int k, int L, string metric, int size, int probes);
        vector<double> Silhouette();
        // Initialization Algorithms
        void findClusters();
        void reinitialize();
        int findSecondMinimum(vector<double> elements);
        void print(vector<double> si, string output, ofstream& myfile);
        vector<vector<Point*>>& getClusters();
        ~Clustering();
};


#endif //LSH_CLUSTERING_H
