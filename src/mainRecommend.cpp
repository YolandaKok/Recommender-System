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
#include <unordered_map>

using namespace std;

int main(int argc, char* argv[]) {

    bool validate = false;
    char *inputFile = NULL, *outputFile = NULL;
    // Number of the default Nearest Neighbors
    int P = 20, size;
    srand(time(NULL));

    // Read Dictionary
    unordered_map<string, double> dictionary;
    readDictionary("datasets/vader_lexicon.csv", &dictionary, '\t');

    // Read Coins
    unordered_map<string, int> coins_queries;
    vector<string> coins;

    readCoins("datasets/coins_queries.csv", &coins_queries, &coins, '\t');
    cout << coins_queries["@bitcoin"] << endl;

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

    /* Read Dictionary */


    // Read Input File
    map<string, vector<Tweet*>> tweets_per_user;
    tweets_per_user = readFileRecommend(inputFile, size, true, P, '\t');

    vector<string> user_ids;
    vector<Sentiment*> sentiments;
    Sentiment *sentiment;

    for(map<string,vector<Tweet*>>::iterator it = tweets_per_user.begin(); it != tweets_per_user.end(); ++it) {
        user_ids.push_back(it->first);
    }
    /*for(int i = 0; i < 3; i++) {
        for(int j = 0; j < tweets_per_user[user_ids.at(0)].at(i)->getWords().size(); j++) {
            cout << tweets_per_user[user_ids.at(0)].at(i)->getWords().at(j) << endl;
        }
    }*/
    //cout << user_ids.at(0) << endl;
    for( int i = 0; i < user_ids.size(); i++ ) {
        //cout << user_ids.at(i) << endl;
        //tweets_per_user[user_ids.at(i)].at(0)->print();
        sentiment = new Sentiment(coins_queries, dictionary, coins_queries.size(), user_ids.at(i), tweets_per_user[user_ids.at(i)]);
        cout << "user_ids " << user_ids.at(i) << endl;
        sentiment->computeUserSentiment();
        sentiments.push_back(sentiment);
        delete sentiment;
    }

    string key = "24";

    /*for( int i = 0; i < tweets_per_user[key].size(); i++ ) {
        tweets_per_user[key].at(i)->print();
    }*/

    /* Deallocate memory */
    //for(int i = 0; i < tweets_per_user.size(); i++)

    /* Free memory for the tweets */
    /*for( int i = 0; i < user_ids.size(); i++ ) {
        for( int j = 0; j < tweets_per_user[user_ids.at(i)].size(); j++ ) {
            delete tweets_per_user[user_ids.at(i)].at(j);
        }
    }*/

    free(inputFile); free(outputFile);

    return 1;
}
