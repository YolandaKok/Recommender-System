//
// Created by yolanda on 10/11/2018.
//

#ifndef LSH_KMEANSPPINIT_H
#define LSH_KMEANSPPINIT_H


#include "Point.h"
#include "Initialization.h"

class KmeansppInit: public Initialization {
    public:
        KmeansppInit();
        vector<Point*>findCentroids(vector<Point*> dataset, int clusters);
        double minimum(vector<double> elements);
        double sum(vector<double> elements);
        double maximum(vector<double> elements);
        double binarySearch(vector<double> arr, int l, int r, double x);
};


#endif //LSH_KMEANSPPINIT_H
