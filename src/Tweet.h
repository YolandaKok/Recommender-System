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
        int findCoin(vector<string> coins);
        vector<string>& getWords();
        void print();
        string getId();
        ~Tweet();
};

#endif //LSH_TWEET_H
