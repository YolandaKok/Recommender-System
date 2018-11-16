//
// Created by yolanda on 15/11/2018.
//

#ifndef LSH_PAMUPDATE_H
#define LSH_PAMUPDATE_H


#include "Update.h"

class PAMUpdate: public Update {
    public:
        bool updateCentroids(vector<Point*>& dataset, vector<Point*>& centroids);
        int minimum_index(vector<double> elements);
        int findSecondMinimum(vector<double> elements);
};


#endif //LSH_PAMUPDATE_H
