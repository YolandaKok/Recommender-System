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
#include "ClusterRecommend.h"
#include <unordered_map>

using namespace std;

random_device rd;
mt19937 gen(rd());

default_random_engine generator(rd());

int main(int argc, char* argv[]) {

    bool validate = false;
    char *inputFile = NULL, *outputFile = NULL;
    // Number of the default Nearest Neighbors
    int P = 20, input_size;
    int L = 3, k = 8, size;
    double w = 4.0, R = 0.0;
    string metric("euclidean");
    srand(time(NULL));

    // Read Dictionary
    unordered_map<string, double> dictionary;
    readDictionary("datasets/vader_lexicon.csv", &dictionary, '\t');

    // Read Coins
    unordered_map<string, int> coins_queries;
    vector<string> coins;

    // Get Coins names
    vector<string> coin_names;
    readCoins("datasets/coins_queries.csv", &coins_queries, &coins, &coin_names, '\t');

    cout << "Coins size: " << coin_names.size() << endl;

    /* Read Arguments */
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
    map<string, Tweet*> tweets, tweets1;
    tweets_per_user = readFileRecommend(inputFile, input_size, true, P, '\t', &tweets);

    // Create a map between the id and the tweet
    tweets1 = readFileRecommendMap(inputFile, input_size, true, P, '\t');

    vector<int> user_ids;
    Sentiment *sentiment;

    // Find user ids
    for(map<int,vector<Tweet*>>::iterator it = tweets_per_user.begin(); it != tweets_per_user.end(); ++it) {
        user_ids.push_back(it->first);
    }

    vector<string> tweets_ids;
    for(map<string, Tweet*>::iterator it = tweets1.begin(); it != tweets1.end(); ++it) {
        tweets_ids.push_back(it->first);
    }

    // Input for Lsh
    vector<Point*> users;
    Point *user;

    cout << "Creating user vectors ..." << endl;
    // Find Sentiment for every user and remove the zero users
    for( int i = 0; i < user_ids.size(); i++ ) {
        sentiment = new Sentiment(coins_queries, dictionary, coin_names.size(), user_ids.at(i), tweets_per_user[user_ids.at(i)]);
        user = sentiment->computeUserSentiment();
        if(user == nullptr) {
            user_ids.erase (user_ids.begin() + i);
        }
        else {
            users.push_back(user);
        }
        delete sentiment;
    }

    cout << "Created user vectors ..." << endl;

    ofstream myfile;
    myfile.open(outputFile);

    cout << "Starting question 1A" << endl;
    // Question 1A !
    vector<tuple<string, vector<string>>> coins_per_user;
    LshRecommend *lshRecommend = new LshRecommend(L, size, k, users, "cosine", input_size, users.at(0)->getDimension(), w, P);
    coins_per_user = lshRecommend->getRecommendations(coin_names, 5);
    lshRecommend->print(outputFile, "1A", myfile);
    delete lshRecommend;
    // End of 1A

    cout << "Completed 1A" << endl;

    cout << "Starting question 2A" << endl;
    // Recommendation through clustering
    int probes = 20;
    vector<string> initialization = {"random_selection", "k-means++"};
    vector<string> assignment = {"Lloyds", "RangeLSH", "RangeHypercube"};
    vector<string> update = {"k-means", "PAM"};
    // Question 2A
    vector<tuple<string, vector<string>>> coins_per_user1;
    ClusterRecommend *clusterRecommend = new ClusterRecommend(users, P, initialization.at(0), assignment.at(0), update.at(0), k, L,
            "euclidean", users.size(), probes, w);
    coins_per_user1 = clusterRecommend->getRecommendations(coin_names, 5);
    clusterRecommend->print(outputFile, "2A", myfile);
    delete clusterRecommend;
    // End of 2A
    cout << "Completed 2A" << endl;

    /* Preprocessing for 2B */
    /* Read tweets from the second assignment */
    char sep = ',';
    vector<Point*> input;
    input = readFile("datasets/twitter_dataset_small_v2.csv", k, size, 1, R, metric, sep);

    int clusters = 200;
    Clustering *tweetsClustering;
    tweetsClustering = new Clustering(clusters, input, initialization.at(0), assignment.at(0), update.at(0), k, L, metric, size, probes, w);
    tweetsClustering->findClusters();
    //vector<vector<Point*>> final_clusters = tweetsClustering->getClusters();
    map<string,int> which_cluster = tweetsClustering->getWhichCluster();
    delete tweetsClustering;

    vector<Point*> output;

    cout << "Creating virtual users' vectors" << endl;
    // Compute Sentiments for every cluster
    Sentiment *tweetsSentiment = new Sentiment(coins_queries, dictionary, coin_names.size(), input);
    tweetsSentiment->computeTweetSentiment(tweets1, which_cluster, &output, clusters, coin_names.size());
    delete tweetsSentiment;
    cout << "Created virtual users' vectors" << endl;

    cout << "Starting 1B" << endl;
    // LSH using the cluster users - 1B
    vector<tuple<string, vector<string>>> coins_per_user2;
    int size1;
    LshRecommend *lshRecommend2 = new LshRecommend(L, size1, k, output, "cosine", output.size(), output.at(0)->getDimension(), w, P, users);
    coins_per_user2 = lshRecommend2->getRecommendations(coin_names, 2);
    lshRecommend2->print(outputFile, "1B", myfile);
    delete lshRecommend2;

    // End of 1B
    cout << "Completed 1B" << endl;

    // 2B Exercise !

    cout << "Starting 2B" << endl;

    //vector<tuple<string, vector<string>>> coins_per_user;
    ClusterRecommend *clusterRecommend2 = new ClusterRecommend(output, P, initialization.at(0), assignment.at(0), update.at(0), k, L,
                                                              "euclidean", output.size(), probes, w, users);
    coins_per_user = clusterRecommend2->getRecommendations(coin_names, 2);
    clusterRecommend2->print(outputFile, "2B", myfile);
    delete clusterRecommend2;

    cout << "Completed 2B" << endl;

    /* Free memory for the tweets */
    for( int i = 0; i < user_ids.size(); i++ ) {
        for( int j = 0; j < tweets_per_user[user_ids.at(i)].size(); j++ ) {
            delete tweets_per_user[user_ids.at(i)].at(j);
        }
    }

    for( int i = 0; i < tweets_ids.size(); i++ ) {
        delete tweets1[tweets_ids.at(i)];
    }

    for(int i = 0; i < users.size(); i++)
        delete users.at(i);

    for( int i = 0; i < output.size(); i++ ) {
        delete output.at(i);
    }

    free(inputFile); free(outputFile);

    myfile.close();

    return 1;
}
