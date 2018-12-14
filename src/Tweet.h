#ifndef LSH_TWEET_H
#define LSH_TWEET_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Tweet {
    private:
        string tweet_id;
        string user_id;
        vector<string> words;
    public:
        Tweet(string tweet_id);
        // getters and setters
        void addWord(string word);
        vector<string>& getWords();
        void print();
        ~Tweet();
};

#endif //LSH_TWEET_H
