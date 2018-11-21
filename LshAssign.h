//
// Created by yolanda on 13/11/2018.
//

#ifndef LSH_LSHASSIGN_H
#define LSH_LSHASSIGN_H


#include "Assignment.h"
#include "Lsh.h"
#include "Hypercube.h"

class LshAssign: public Assignment {
    private:
        LSH *lsh;
        Hypercube *cube;
        void combinationUtil(vector<int> arr, int n, int r, int index, vector<int> data, int i, vector<pair<int,int>>& results);
        double minimum(vector<double> elements);
        int minimum_index(vector<double> elements);
    public:
        LshAssign(LSH *lsh, Hypercube *cube);
        void assignCentroids(vector<Point*>& dataset, vector<Point*> centroids);
};


#endif //LSH_LSHASSIGN_H
