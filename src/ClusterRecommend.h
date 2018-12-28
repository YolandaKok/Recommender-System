//
// Created by yolanda on 28/12/2018.
//

#ifndef LSH_CLUSTERRECOMMEND_H
#define LSH_CLUSTERRECOMMEND_H
#include "Clustering.h"
#include "Point.h"
#include <vector>

class ClusterRecommend {
    private:
        Clustering *clustering;
        vector<Point*> points;
    public:
        ClusterRecommend(vector<Point*> dataset, int P, string init, string assign, string update, int k, int L, string metric, int size, int probes, double w);
        vector<tuple<string, vector<string>>> getRecommendations(vector<string>& coin_names);
        ~ClusterRecommend();
};

#endif //LSH_CLUSTERRECOMMEND_H
