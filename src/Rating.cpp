//
// Created by yolanda on 23/12/2018.
//

#include "Rating.h"
#include <vector>
#include "Point.h"
#include <tuple>
#include <cmath>
#include <iostream>
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

void Rating::mainRating() {
    // Sum of the similarities
    double sum = 0.0;
    vector<double> estimated_ratings;
    for(int j = 0; j < this->neighbors.at(0)->getDimension(); j++ ) {
        for (int i = 0; i < this->neighbors.size(); i++) {
            sum += ratingForItem(this->neighbors.at(i), j, i);
        }
        sum = sum * this->z;
        cout << sum << endl;
        estimated_ratings.push_back(sum);
        sum = 0.0;
    }
}

double Rating::ratingForItem(Point *user, int coin, int user_index) {
    // Rating for item i (coin i)
    double result;
    result = this->similarity_array.at(user_index) * user->getCoord(coin);
    return result;
}

Rating::~Rating() {

}