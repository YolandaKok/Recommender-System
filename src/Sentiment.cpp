#include <iostream>
#include <vector>
#include <map>
#include "Sentiment.h"
#include "Tweet.h"
#include <string>
#include <cmath>

using namespace std;

Sentiment::Sentiment() {

}

Sentiment::Sentiment(vector<string> coins, map<string, double> dictionary, int dimension, string userId, vector<Tweet*> tweets) {
    this->userId = userId;
    this->dimension = dimension;
    this->tweets = tweets;
    this->coins = coins;
    this->dictionary = dictionary;
    this->user_sentiments.resize(dimension);
    this->user_sentiments_per_coin.resize(dimension);
    for(int i = 0; i < dimension; i++) {
        this->user_sentiments[i] = 0.0;
        this->user_sentiments_per_coin[i] = 0;
    }
}

vector<double> Sentiment::computeUserSentiment() {
    /* For each tweet */
    int coin_index;
    vector<string> words;
    double sum = 0.0;
    int count = 0;
    for( int i = 0; i < tweets.size(); i++ ) {
        /* For each word */
        coin_index = tweets.at(i)->findCoin(this->coins);
        cout << coin_index << endl;
        /* Find Sentiment Result */
        words = this->tweets.at(i)->getWords();
        for( int j = 0; j < words.size(); j++ ) {
            //cout << words.at(j) << endl;
            //cout << dictionary[words.at(j)] << endl;
            // Normalization
            sum += dictionary[words.at(j)];
        }
        double si = normalizeSi(sum, 15.0);
        //cout << coin_index << endl;
        this->user_sentiments[coin_index] += si;
        sum = 0.0;
    }
    cout << this->user_sentiments[3] << endl;
    return this->user_sentiments;
}

/* Return Coin Index */
int Sentiment::findCoin(vector<string> coins, string word) {
    bool found = false;
    int index;

    for( int i = 0; i < coins.size(); i++ ) {
        if(coins.at(i).compare(word) == 0) {
            found = true;
            index = i;
        }
    }
    if(found)
        return index;
    else
        return -1;
}

/* Normalize sentiment */
double Sentiment::normalizeSi(double totalscore, double alpha) {
    double si;
    si = totalscore / sqrt((totalscore * totalscore) + alpha);
    return si;
}

Sentiment::~Sentiment() {

}