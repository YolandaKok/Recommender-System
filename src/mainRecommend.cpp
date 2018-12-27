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
#include "LshRecommend.h"
#include <unordered_map>

using namespace std;

random_device rd;
default_random_engine generator(rd());

int main(int argc, char* argv[]) {

    bool validate = false;
    char *inputFile = NULL, *outputFile = NULL;
    // Number of the default Nearest Neighbors
    int P = 20, input_size;
    int L = 10, k = 15, size;
    double w = 4.0;
    srand(time(NULL));

    // Read Dictionary
    unordered_map<string, double> dictionary;
    readDictionary("datasets/vader_lexicon.csv", &dictionary, '\t');

    // Read Coins
    unordered_map<string, int> coins_queries;
    vector<string> coins;

    vector<string> coin_names;
    readCoins("datasets/coins_queries.csv", &coins_queries, &coins, &coin_names, '\t');

    for(int i = 0; i < coin_names.size(); i++) {
        cout << coin_names.at(i) << endl;
    }

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
    map<int, vector<Tweet*>> tweets_per_user;
    tweets_per_user = readFileRecommend(inputFile, input_size, true, P, '\t');

    vector<int> user_ids;
    vector<Sentiment*> sentiments;
    Sentiment *sentiment;

    for(map<int,vector<Tweet*>>::iterator it = tweets_per_user.begin(); it != tweets_per_user.end(); ++it) {
        user_ids.push_back(it->first);
    }

    cout << input_size << " input_size" << endl;

    // Input for Lsh
    vector<Point*> points;
    Point *point;

    for( int i = 0; i < user_ids.size(); i++ ) {
        sentiment = new Sentiment(coins_queries, dictionary, 100, user_ids.at(i), tweets_per_user[user_ids.at(i)]);
        point = sentiment->computeUserSentiment();
        if(point == nullptr) {
            // erase user
            user_ids.erase (user_ids.begin() + i);
        }
        else {
            points.push_back(point);
        }
        delete sentiment;
    }

    cout << points.size() << endl;
    points.at(9)->print();
    cout << endl;
    cout << points.at(9)->getId() << " Id" << endl;
    vector<tuple<string, vector<string>>> coins_per_user;
    LshRecommend *lshRecommend = new LshRecommend(L, size, k, points, "cosine", input_size, points.at(0)->getDimension(), w, P);
    coins_per_user = lshRecommend->getRecommendations(coin_names);
    delete lshRecommend;

    for(int i = 0; i < coins_per_user.size(); i++) {
        cout << "<u" << get<0>(coins_per_user.at(i)) << ">: ";
        vector<string> coins_recommendations = get<1>(coins_per_user.at(i));
        for(int j = 0; j < coins_recommendations.size(); j++) {
            cout << coins_recommendations.at(j) << " ";
        }
        cout << endl;
    }

    // TODO: Recommendation Base Class
    // TODO: Learn about the recommendation type
    // Create LSH Recommendation
    // Create Clustering recommendation using euclidean and k-means for users

    /* Free memory for the sentiments */
    for( int i = 0; i < points.size(); i++ ) {
        delete points.at(i);
    }

    /* Free memory for the tweets */
    for( int i = 0; i < user_ids.size(); i++ ) {
        for( int j = 0; j < tweets_per_user[user_ids.at(i)].size(); j++ ) {
            delete tweets_per_user[user_ids.at(i)].at(j);
        }
    }

    free(inputFile); free(outputFile);

    return 1;
}
