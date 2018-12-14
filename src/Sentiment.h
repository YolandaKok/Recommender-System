//
// Created by yolanda on 14/12/2018.
//

#ifndef LSH_SENTIMENT_H
#define LSH_SENTIMENT_H
#include "Tweet.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Sentiment {
    private:
        int dimension;
        // Sentiments
        vector<double> user_sentiments;
        // Maybe the dictionary for the sentiments
        // Maybe the vector with the coins
        string userId;
        // Tweets for the current user
        vector<Tweet*> tweets;
    public:
        Sentiment();
        vector<double> user_sentiments;
        ~Sentiment();
};

#endif //LSH_SENTIMENT_H
