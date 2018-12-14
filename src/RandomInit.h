//
// Created by yolanda on 10/11/2018.
//

#ifndef LSH_RANDOMINIT_H
#define LSH_RANDOMINIT_H


#include "Initialization.h"

class RandomInit: public Initialization {
    public:
        vector<Point*>findCentroids(vector<Point*> dataset, int clusters);
};


#endif //LSH_RANDOMINIT_H
