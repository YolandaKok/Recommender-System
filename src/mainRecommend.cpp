#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <cstring>
#include "Tweet.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {

    bool validate = false;
    char *inputFile = NULL, *outputFile = NULL;
    // Number of the default Nearest Neighbors
    int P = 20;
    srand(time(NULL));

    vector<string> coins = {"ethereum", "bitcoin", "stellar", "tether"};
    map<string, double> dictionary;
    dictionary["bad"] = -2.0;
    dictionary["good"] = 2.0;
    dictionary["profitable"] = 1.5;

    for(int i = 1; i < argc; i += 2) {
        /* Input File */
        if(!strcmp(argv[i], "-d")) {
            inputFile = (char*)malloc(strlen(argv[i+1]) + 1);
            strcpy(inputFile, argv[i+1]);
        }
            /* Configuration File */
        else if(!strcmp(argv[i], "-o")) {
            outputFile = (char*)malloc(strlen(argv[i+1]) + 1);
            strcpy(outputFile, argv[i+1]);
        }
        else if(!strcmp(argv[i], "-validate")) {
            validate = true;
        }
    }

    Tweet *tweet = new Tweet("123");
    tweet->addWord("hey");
    tweet->addWord("bitcoin");
    tweet->addWord("great");

    Tweet *tweet1 = new Tweet("123");
    tweet1->addWord("ethereum");
    tweet1->addWord("bad");
    tweet1->addWord("maybe");

    //delete tweet;


    // Read Input File
    map<int, vector<Tweet*>> Tweets_per_User;
    Tweets_per_User[1].push_back(tweet);
    Tweets_per_User[1].push_back(tweet1);

    Tweets_per_User[1].at(0)->print();
    Tweets_per_User[1].at(1)->print();


    multimap<int, Tweet*> tweets;
    tweets.insert(pair <int, Tweet*> (1, tweet));
    tweets.insert(pair <int, Tweet*> (1, tweet1));

    int key = 1;
    for (auto itr = tweets.begin(); itr != tweets.end(); itr++)
        if (itr -> first == key) {
            cout << itr->first << " ";
            itr->second->print();
        }

    return 1;
}
