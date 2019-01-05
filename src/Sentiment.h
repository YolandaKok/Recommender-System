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
#include <unordered_map>
#include "Point.h"
using namespace std;

class Sentiment {
    private:
        int dimension;
        // Sentiments for coins
        vector<double> user_sentiments;
        // maybe it's not necessary cause it depends on the sum not the mean value
        vector<int> user_sentiments_per_coin;
        // Maybe the dictionary for the sentiments
        unordered_map<string, double> dictionary;
        // Maybe the vector with the coins
        unordered_map<string, int> coins_queries;
        int userId;
        // Tweets for the current user
        vector<Tweet*> tweets;
        string coin;
        // Point * ui
        Point* point;
        void subtractAverage();
        // Which coins sentiment modified
        vector<int> modified;
        //vector<vector<Point*>> clusters;
        vector<Point*> input;
        //vector<Point*> clusterSentiment;
    public:
        Sentiment();
        Sentiment(unordered_map<string, int> coins_queries, unordered_map<string, double> dictionary, int dimension, int userId, vector<Tweet*> tweets);
        Sentiment(unordered_map<string, int>& coins_queries, unordered_map<string, double>& dictionary,
               int dimension, vector<Point*> input);
        int findCoin(vector<string> coins, string word);
        Point* computeUserSentiment();
        double normalizeSi(double totalscore, double alpha);
        void computeTweetSentiment(map<string, Tweet*> map_tweets, map<string,int>& which_cluster, vector<Point*> *output);
        ~Sentiment();
};

#endif //LSH_SENTIMENT_H
