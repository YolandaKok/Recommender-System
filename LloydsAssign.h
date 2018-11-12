//
// Created by yolanda on 10/11/2018.
//

#ifndef LSH_LLOYDSASSIGN_H
#define LSH_LLOYDSASSIGN_H


#include "Assignment.h"

class LloydsAssign: public Assignment {
    public:
        void assignCentroids(vector<Point*>& dataset, vector<Point*> centroids);
        int minimum_index(vector<double> elements);
        int findSecondMinimum(vector<double> elements);
};


#endif //LSH_LLOYDSASSIGN_H
