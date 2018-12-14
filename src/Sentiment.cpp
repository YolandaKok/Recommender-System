#include <iostream>
#include <vector>
#include <map>
#include "Sentiment.h"

using namespace std;

Sentiment::Sentiment(vector<string> coins, map<string, double> dictionary, int dimension, string userId, vector<Tweet*> tweets) {
    this->userId = userId;
    this->dimension = dimension;
    this->tweets = tweets;
    this->coins = coins;
    this->dictionary = dictionary;
}

vector<double> Sentiment::computeUserSentiment() {
    /* For each tweet */
    int coin_index;
    vector<string> words;
    for( int i = 0; i < tweets.size(); i++ ) {
        /* For each word */
        words = this->tweets.at(i)->getWords();
        for( int j = 0; j < words.size(); j++ ) {
            /* Find the coin */
            coin_index = findCoin(coins, words.at(j));
            if(coin_index >= 0)
                this->coin = this->coins[coin_index];
            //cout << coin_index << endl;
            //cout << dictionary[words.at(j)] << endl;
        }
        cout << this->coin << endl;
    }
}

/* Return Coin Index */
int Sentiment::findCoin(vector<string> coins, string word) {
    bool found = false;
    int index;

    for( int i = 0; i < coins.size(); i++ ) {
        if(!coins.at(i).compare(word)) {
            found = true;
            index = i;
        }
    }
    if(found)
        return index;
    else
        return -1;
}