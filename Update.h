//
// Created by yolanda on 10/11/2018.
//

#ifndef LSH_UPDATE_H
#define LSH_UPDATE_H


#include "Point.h"
#include <vector>

class Update {
    public:
        virtual vector<Point*> updateCentroids(vector<Point*> dataset, vector<Point*> centroids) = 0;
};


#endif //LSH_UPDATE_H
