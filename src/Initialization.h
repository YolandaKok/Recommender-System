//
// Created by yolanda on 10/11/2018.
//

#ifndef LSH_INITIALIZATION_H
#define LSH_INITIALIZATION_H


#include "Point.h"

class Initialization {
    public:
        // Pure virtual function Return Centroids
        virtual vector<Point*>findCentroids(vector<Point*> dataset, int clusters);
};


#endif //LSH_INITIALIZATION_H
