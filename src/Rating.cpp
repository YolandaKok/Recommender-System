//
// Created by yolanda on 23/12/2018.
//

#include "Rating.h"
#include <vector>
#include "Point.h"
#include <tuple>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

Rating::Rating(Point *query, vector<Point*> neighbors) {
    this->query = query;
    this->query->subtractAverage();
    this->neighbors = neighbors;
    for( int i = 0; i < neighbors.size(); i++ ) {
        if(this->query->getId().compare(neighbors.at(i)->getId()) != 0) {
            neighbors.at(i)->subtractAverage();
        }
    }
    this->z = calculateZ();
}

// Calculate the abs value of sum of all similarities
double Rating::calculateZ() {
    double sum = 0.0, result;
    for( int i = 0; i < neighbors.size(); i++ ) {
        result = query->cosine_similarity(neighbors.at(i));
        this->similarity_array.push_back(result);
        result = abs(result);
        sum += result;
    }
    return 1 / sum;
}

vector<int> Rating::mainRating() {
    // Sum of the similarities
    double sum = 0.0;
    vector<double> estimated_ratings;
    Point *point = new Point();
    vector<tuple<double, int>> coin_rating;
    vector<int> recommended_coins;
    for(int j = 0; j < this->neighbors.at(0)->getDimension(); j++ ) {
        for (int i = 0; i < this->neighbors.size(); i++) {
            sum += ratingForItem(this->neighbors.at(i), j, i);
        }
        sum = sum * this->z;
        //cout << sum << endl;
        point->setId(this->query->getId());
        point->addCoord(sum);
        estimated_ratings.push_back(sum);
        if(this->query->findModified(j) == 0) {
            coin_rating.push_back(make_tuple(sum, j));
        }
        sum = 0.0;
    }
    sort(coin_rating.begin(), coin_rating.end(), sortdesc);
    cout << "lala" << endl;
    for(int i = 0; i < 5; i++) {
        //cout << get<0>(coin_rating.at(i)) << endl;
        cout << get<1>(coin_rating.at(i)) << " coin" << endl;
        recommended_coins.push_back(get<1>(coin_rating.at(i)));
    }
    cout << "lala" << endl;
    cout << endl;
    // Estimated Ratings for every coin
    //point->print();
    // From query find the modified and exclude them from the results
    return recommended_coins;
}

// by first element of tuples in descending order
bool Rating::sortdesc(const tuple<double, int>& a, const tuple<double, int>& b) {
    return (get<0>(a) > get<0>(b));
}

double Rating::ratingForItem(Point *user, int coin, int user_index) {
    // Rating for item i (coin i)
    double result;
    result = this->similarity_array.at(user_index) * user->getCoord(coin);
    return result;
}

Rating::~Rating() {

}