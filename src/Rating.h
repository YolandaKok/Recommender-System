//
// Created by yolanda on 23/12/2018.
//

#ifndef LSH_RATING_H
#define LSH_RATING_H
#include <vector>
#include "Point.h"
#include <tuple>

class Rating {
    private:
        vector<Point*> neighbors;
        Point *query;
        vector<double> similarity_array;
        double z;
    public:
        Rating(Point *query, vector<Point*> neighbors);
        // Calculate z -> the normalizing factor
        double calculateZ();
        // Calculate Rating for i item
        double ratingForItem(Point *user, int coin, int user_index);
        // Main Rating
        void mainRating();
        // Find the k most rated coins
        ~Rating();
};

#endif //LSH_RATING_H
