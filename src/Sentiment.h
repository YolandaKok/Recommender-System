//
// Created by yolanda on 14/12/2018.
//

#ifndef LSH_SENTIMENT_H
#define LSH_SENTIMENT_H
#include "Tweet.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

class Sentiment {
    private:
        int dimension;
        // Sentiments
        vector<double> user_sentiments;
        // Maybe the dictionary for the sentiments
        map<string, double> dictionary;
        // Maybe the vector with the coins
        vector<string> coins;
        string userId;
        // Tweets for the current user
        vector<Tweet*> tweets;
        string coin;
    public:
        Sentiment(vector<string> coins, map<string, double> dictionary, int dimension, string userId, vector<Tweet*> tweets);
        int findCoin(vector<string> coins, string word);
        vector<double> computeUserSentiment();
        ~Sentiment();
};

#endif //LSH_SENTIMENT_H
