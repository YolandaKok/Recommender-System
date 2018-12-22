#include <iostream>
#include <vector>
#include <map>
#include "Sentiment.h"
#include "Tweet.h"
#include <string>
#include <cmath>
#include <unordered_map>
#include "Point.h"

using namespace std;

Sentiment::Sentiment() {

}

Sentiment::Sentiment(unordered_map<string, int> coins_queries, unordered_map<string, double> dictionary, int dimension, int userId, vector<Tweet*> tweets) {
    this->userId = userId;
    this->dimension = dimension;
    this->tweets = tweets;
    this->coins_queries = coins_queries;
    this->dictionary = dictionary;
    this->user_sentiments.resize(dimension);
    this->user_sentiments_per_coin.resize(dimension);
    this->point = new Point();
    for(int i = 0; i < dimension; i++) {
        this->user_sentiments[i] = 0.0;
        this->user_sentiments_per_coin[i] = 0;
        this->point->addCoord(0.0);
    }
}

/* Return a point */
Point* Sentiment::computeUserSentiment() {
    /* For each tweet */
    vector<int> coin_indexes;
    vector<string> words;
    double sum = 0.0;
    int count = 0;
    //point = new Point();
    /* Save which one changes */
    for( int i = 0; i < tweets.size(); i++ ) {
        words = this->tweets.at(i)->getWords();
        for( int j = 0; j < this->tweets.at(i)->getWords().size(); j++ ) {
            if(this->coins_queries[words.at(j)] != 0) {
                coin_indexes.push_back(this->coins_queries[words.at(j)]);
            }
            sum += dictionary[words.at(j)];
        }
        // Normalization
        double si = normalizeSi(sum, 15.0);
        // Save the user sentiment
        for( int j = 0; j < coin_indexes.size(); j++ ) {
            // Save which was modified
            if(!this->point->findModified(coin_indexes.at(j) - 1)) {
                this->point->modifyCoord(coin_indexes.at(j) - 1, si);
                this->point->addModified(coin_indexes.at(j) - 1);
            }
        }
        sum = 0.0;
        coin_indexes.clear();
    }
    // Compute average and subtract it from a every known sentiment
    //subtractAverage();
    // Subtract average from the modified
    this->point->subtractAverage();
    this->point->computeAverage();
    this->point->setId(to_string(this->userId));
    return this->point;
}

void Sentiment::subtractAverage() {
    double sum = 0.0;
    // For every modified coin sentiment
    for( int i = 0; i < this->modified.size(); i++ ) {
        sum += this->user_sentiments[modified.at(i)];
    }

    sum /= this->modified.size();

    for( int i = 0; i < this->modified.size(); i++ ) {
        this->user_sentiments[this->modified.at(i)] -= sum;
    }
}

// TODO: Remove it, if it's not necessary
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