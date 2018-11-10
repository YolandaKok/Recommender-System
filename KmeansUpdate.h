//
// Created by yolanda on 10/11/2018.
//

#ifndef LSH_KMEANSUPDATE_H
#define LSH_KMEANSUPDATE_H


#include "Update.h"

class KmeansUpdate: public Update {
    public:
        vector<Point*> updateCentroids(vector<Point*> dataset, vector<Point*> centroids);
};


#endif //LSH_KMEANSUPDATE_H
