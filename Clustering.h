#ifndef LSH_CLUSTERING_H
#define LSH_CLUSTERING_H

#include "Point.h"

class Clustering {
    private:
        // Clusters Structure
        vector<vector<Point*>> clusters;
        // Num of clusters
        int num_clusters;
        // Input Points
        vector<Point*> dataset;
        // Centroids
        vector<Point*> centroids;
    public:
        Clustering(int num_clusters, vector<Point*> dataset);
        // Initialization Algorithms
        void randomSelection();
        void k_means_pp();
        // Assignment Algorithms

        // Update Algorithms

        // Utils
        double minimum(vector<double> elements);
        double sum(vector<double> elements);
        ~Clustering();
};


#endif //LSH_CLUSTERING_H
