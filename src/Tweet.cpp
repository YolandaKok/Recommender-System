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

vector<string>& Tweet::getWords() {
    return this->words;
}

void Tweet::print() {
    for( int i = 0; i < this->words.size(); i++ ) {
        cout << words.at(i) << " ";
    }
    cout << endl;
}

Tweet::~Tweet() {

}

