#include "LshRecommend.h"
#include <iostream>
#include "Lsh.h"
#include <vector>
#include "Point.h"
#include "Rating.h"

using namespace std;

LshRecommend::LshRecommend(int L, int size, int k, vector<Point *> points, string lsh_family, int input_size,
                           double dimension, double w, int P) {

    this->lsh = new LSH(L, size, k, points, lsh_family, input_size, dimension, w);
    this->user_points = points;
    this->P = P;
}

vector<tuple<string, vector<string>>> LshRecommend::getRecommendations(vector<string>& coin_names) {
    //this->lsh->bucket();
    vector<Point*> neighbors;
    vector<tuple<string, vector<string>>> recommended_coins;
    vector<string> coins;
    vector<int> coins_indexes;
    int count = 0;
    for(int i = 0; i < this->user_points.size(); i++) {
        neighbors = this->lsh->rangeSearchAll(user_points.at(i));
        // Find if neighbors are > P
        if(neighbors.size() > this->P) {
            // truncate some results from the vector
            neighbors.resize(P);
            // cout << neighbors.at(0)->getId() << " neighbor id" << endl;
        }
        cout << neighbors.size() << " neighbors" << endl;
        if(neighbors.size() == 0) {
            count++;
        }
        else {
            Rating *rating = new Rating(user_points.at(i), neighbors);
            coins_indexes = rating->mainRating();
            for(int j = 0; j < coins_indexes.size(); j++) {
                coins.push_back(coin_names.at(coins_indexes.at(j)));
            }
            recommended_coins.push_back(make_tuple(user_points.at(i)->getId(), coins));
            coins.clear();
            //coins_indexes.clear();
            delete rating;
        }
    }
    // For every user recommend k coins
    return recommended_coins;
}

LshRecommend::~LshRecommend() {
    delete this->lsh;
}
