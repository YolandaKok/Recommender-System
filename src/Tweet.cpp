#include <iostream>
#include "Tweet.h"
#include <vector>
#include <string>
using namespace std;

Tweet::Tweet(string tweet_id) {
    this->tweet_id = tweet_id;
}

void Tweet::addWord(string word) {
    this->words.push_back(word);
}

vector<string> Tweet::getWords() {
    return this->words;
}

int Tweet::findCoin(vector<string> coins) {
    bool found = false;
    int index;

    for( int i = 0; i < coins.size(); i++ ) {
        for(int j = 0; j < this->words.size(); j++) {
            if(coins.at(i).compare(this->words.at(j)) == 0) {
                found = true;
                index = i;
            }
        }
    }
    if(found)
        return index;
    else
        return -1;
}

void Tweet::print() {
    for( int i = 0; i < this->words.size(); i++ ) {
        cout << words.at(i);
    }
    cout << endl;
}

string Tweet::getId() {
    return this->tweet_id;
}

Tweet::~Tweet() {

}

