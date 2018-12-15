#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <cstring>
#include "Tweet.h"
#include <bits/stdc++.h>
#include "IOutils.h"
#include "Sentiment.h"

using namespace std;

int main(int argc, char* argv[]) {

    bool validate = false;
    char *inputFile = NULL, *outputFile = NULL;
    // Number of the default Nearest Neighbors
    int P = 20, size;
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

    // Read Input File
    map<string, vector<Tweet*>> tweets_per_user;
    tweets_per_user = readFileRecommend(inputFile, size, true, P, '\t');

    vector<string> user_ids;
    vector<Sentiment*> sentiments;
    Sentiment *sentiment;

    for(map<string,vector<Tweet*>>::iterator it = tweets_per_user.begin(); it != tweets_per_user.end(); ++it) {
        user_ids.push_back(it->first);
    }

    string key = "4";
    for( int i = 0; i < tweets_per_user[key].size(); i++ ) {
        tweets_per_user[key].at(i)->print();
    }

    for( int i = 0; i < user_ids.size(); i++ ) {
        //cout << user_ids.at(i) << endl;
        //tweets_per_user[user_ids.at(i)].at(0)->print();
        sentiment = new Sentiment(coins, dictionary, coins.size(), user_ids.at(i), tweets_per_user[user_ids.at(i)]);
        sentiment->computeUserSentiment();
        sentiments.push_back(sentiment);
        delete sentiment;
    }

    /* string key = "3";

    for( int i = 0; i < tweets_per_user[key].size(); i++ ) {
        tweets_per_user[key].at(i)->print();
    } */

    /* Deallocate memory */
    //for(int i = 0; i < tweets_per_user.size(); i++)

    return 1;
}
