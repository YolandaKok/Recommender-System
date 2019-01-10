#include "LshRecommend.h"
#include <iostream>
#include "Lsh.h"
#include <vector>
#include "Point.h"
#include "Rating.h"

using namespace std;

LshRecommend::LshRecommend(int L, int size, int k, vector<Point *> points, string lsh_family, int input_size,
                           double dimension, double w, int P) {
    this->user_points = points;
    for( int i = 0; i < user_points.size(); i++ ) {
        user_points.at(i)->subtractAverage();
    }
    this->lsh = new LSH(L, size, k, this->user_points, lsh_family, input_size, dimension, w);
    // Normalization with the average
    this->P = P;
}

// Constructor for different query points

LshRecommend::LshRecommend(int L, int size, int k, vector<Point *> points, string lsh_family, int input_size,
                           double dimension, double w, int P, vector<Point *> queries) {
    this->lsh = new LSH(L, size, k, points, lsh_family, input_size, dimension, w);
    this->user_points = queries;
    this->P = P;
}

vector<tuple<string, vector<string>>> LshRecommend::getRecommendations(vector<string>& coin_names, int num_of_coins) {
    //this->lsh->bucket();
    clock_t begin_time = clock();
    vector<Point*> neighbors;
    //vector<tuple<string, vector<string>>> recommended_coins;
    vector<string> coins;
    vector<int> coins_indexes;
    int count = 0;
    for(int i = 0; i < this->user_points.size(); i++) {
        neighbors = this->lsh->rangeSearchAll(user_points.at(i));
        //cout << neighbors.size() << endl;
        // Find if neighbors are > P
        if(neighbors.size() > this->P) {
            // truncate some results from the vector
            neighbors.resize(P);
        }
        //cout << neighbors.size() << " neighbors" << endl;
        if(neighbors.size() == 0) {
            count++;
        }
        else {
            Rating *rating = new Rating(user_points.at(i), neighbors, "cosine");
            coins_indexes = rating->mainRating(num_of_coins);
            for(int j = 0; j < coins_indexes.size(); j++) {
                coins.push_back(coin_names.at(coins_indexes.at(j)));
            }
            this->coins_per_user.push_back(make_tuple(user_points.at(i)->getId(), coins));
            coins.clear();
            //coins_indexes.clear();
            delete rating;
        }
    }
    // For every user recommend k coins
    this->total_time = double( clock () - begin_time ) /  CLOCKS_PER_SEC;
    return this->coins_per_user;
}

void LshRecommend::print(string outputFile, string exercise) {
    ofstream myfile;
    myfile.open(outputFile);
    myfile << "Cosine Lsh" << endl;
    myfile << exercise << endl;
    for( int i = 0; i < this->coins_per_user.size(); i++ ) {
        myfile << "<u" << get<0>(coins_per_user.at(i)) << ">: ";
        vector<string> coins_recommendations = get<1>(coins_per_user.at(i));
        for(int j = 0; j < coins_recommendations.size(); j++) {
            myfile << coins_recommendations.at(j) << " ";
        }
        myfile << endl;
    }
    myfile << "Execution Time: " << this->total_time << "secs" << endl;
    myfile.close();
}

LshRecommend::~LshRecommend() {
    delete this->lsh;
}
