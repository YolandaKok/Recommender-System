#ifndef LSH_CLUSTERING_H
#define LSH_CLUSTERING_H

#include "Point.h"
#include "Initialization.h"
#include "Assignment.h"
#include "Update.h"

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
        // Initialization
        Initialization *initialization;
        // Assignment
        Assignment *assignment;
        // Update
        Update *update;
    public:
        Clustering(int num_clusters, vector<Point*> dataset, string init, string assign, string update);
        // Initialization Algorithms
        void findClusters();
        // Assignment Algorithms

        // Update Algorithms

        // Utils

        ~Clustering();
};


#endif //LSH_CLUSTERING_H
