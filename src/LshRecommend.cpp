#include "LshRecommend.h"
#include <iostream>
#include "Lsh.h"
#include <vector>
#include "Point.h"
#include "Rating.h"

using namespace std;

LshRecommend::LshRecommend(int L, int size, int k, vector<Point *> points, string lsh_family, int input_size,
                           double dimension, double w) {

    this->lsh = new LSH(L, size, k, points, lsh_family, input_size, dimension, w);
    this->user_points = points;
}

void LshRecommend::getRecommendations() {
    //this->lsh->bucket();
    /*for(int i = 0; i < 4; i++) {
        cout << user_points.at(i)->getId() << " user_id" << endl;
        cout << this->lsh->rangeSearchAll(user_points.at(i)).size() << " LshRecommend" << endl;
    }*/

    vector<Point*> neighbors;
    //neighbors.resize(100);
    neighbors = this->lsh->rangeSearchAll(user_points.at(3));
    // For every item create a recommendation using the recommendation filtering algorithm
    //neighbors.resize(20);
    //get<1>(neighbors[1])->getId();
    //neighbors.at(1)->getId();
    Rating *rating = new Rating(user_points.at(3), neighbors);
    rating->mainRating();
    delete rating;
}

LshRecommend::~LshRecommend() {
    delete this->lsh;
}
