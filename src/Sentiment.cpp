#include <iostream>
#include <vector>
#include <map>
#include "Sentiment.h"
#include "Tweet.h"
#include <string>
#include <cmath>
#include <unordered_map>

using namespace std;

Sentiment::Sentiment() {

}

Sentiment::Sentiment(unordered_map<string, int> coins_queries, unordered_map<string, double> dictionary, int dimension, string userId, vector<Tweet*> tweets) {
    this->userId = userId;
    this->dimension = dimension;
    this->tweets = tweets;
    this->coins_queries = coins_queries;
    this->dictionary = dictionary;
    this->user_sentiments.resize(dimension);
    this->user_sentiments_per_coin.resize(dimension);
    for(int i = 0; i < dimension; i++) {
        this->user_sentiments[i] = 0.0;
        this->user_sentiments_per_coin[i] = 0;
    }
    //tweets.at(0)->print();
    vector<string> words;
    words = this->tweets.at(0)->getWords();
    //cout << words.at(0) << endl;

}

void Sentiment::computeUserSentiment() {
    /* For each tweet */
    int coin_index;
    vector<string> words;
    double sum = 0.0;
    int count = 0;
    for( int i = 0; i < tweets.size(); i++ ) {
        //coin_index = this->coins_queries[tweets.at(i)->words];
        //cout << coin_index << endl;
        words = this->tweets.at(i)->getWords();
        for( int j = 0; j < this->tweets.at(i)->getWords().size(); j++ ) {
            if(this->coins_queries[words.at(j)] != 0) {
                coin_index = this->coins_queries[words.at(j)];
            }
            // Normalization
            sum += dictionary[words.at(j)];
        }
        double si = normalizeSi(sum, 15.0);
        //cout << coin_index << endl;
        this->user_sentiments[coin_index-1] += si;
        sum = 0.0;
    }
    cout << this->user_sentiments[1] << endl;
    cout << coin_index << endl;
    //return this->user_sentiments;
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