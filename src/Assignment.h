//
// Created by yolanda on 10/11/2018.
//

#ifndef LSH_ASSIGNMENT_H
#define LSH_ASSIGNMENT_H


#include "Point.h"

class Assignment {
    public:
        string metric;
        Assignment(string metric);
        virtual void assignCentroids(vector<Point*>& dataset, vector<Point*> centroids);
};


#endif //LSH_ASSIGNMENT_H
