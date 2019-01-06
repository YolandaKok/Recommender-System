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
    int L = 10, k = 15, size;
    double w = 4.0, R = 0.0;
    string metric("euclidean");
    srand(time(NULL));

    // Read Dictionary
    unordered_map<string, double> dictionary;
    readDictionary("datasets/vader_lexicon.csv", &dictionary, '\t');

    // Read Coins
    unordered_map<string, int> coins_queries;
    vector<string> coins;

    vector<string> coin_names;
    readCoins("datasets/coins_queries.csv", &coins_queries, &coins, &coin_names, '\t');

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

    tweets1 = readFileRecommendMap(inputFile, input_size, true, P, '\t');

    vector<int> user_ids;
    vector<Sentiment*> sentiments;
    Sentiment *sentiment;

    for(map<int,vector<Tweet*>>::iterator it = tweets_per_user.begin(); it != tweets_per_user.end(); ++it) {
        user_ids.push_back(it->first);
    }

    // Input for Lsh
    vector<Point*> users;
    Point *user;

    for( int i = 0; i < user_ids.size(); i++ ) {
        sentiment = new Sentiment(coins_queries, dictionary, 100, user_ids.at(i), tweets_per_user[user_ids.at(i)]);
        user = sentiment->computeUserSentiment();
        if(user == nullptr) {
            user_ids.erase (user_ids.begin() + i);
        }
        else {
            users.push_back(user);
        }
        delete sentiment;
    }

    cout << users.size() << endl;
    /* vector<tuple<string, vector<string>>> coins_per_user;
    LshRecommend *lshRecommend = new LshRecommend(L, size, k, points, "cosine", input_size, points.at(0)->getDimension(), w, P);
    coins_per_user = lshRecommend->getRecommendations(coin_names);
    lshRecommend->print(outputFile);
    delete lshRecommend;*/

    // Recommendation through clustering
    int probes = 20;
    vector<string> initialization = {"random_selection", "k-means++"};
    vector<string> assignment = {"Lloyds", "RangeLSH", "RangeHypercube"};
    vector<string> update = {"k-means", "PAM"};
    /*vector<tuple<string, vector<string>>> coins_per_user;
    ClusterRecommend *clusterRecommend = new ClusterRecommend(points, P, initialization.at(0), assignment.at(0), update.at(0), k, L,
            "euclidean", points.size(), probes, w);
    coins_per_user = clusterRecommend->getRecommendations(coin_names);
    clusterRecommend->print(outputFile);
    delete clusterRecommend;*/



    /* Read tweets from the second assignment */
    char sep = ',';
    vector<Point*> input;
    input = readFile("datasets/twitter_dataset_small_v2.csv", k, size, 1, R, metric, sep);

    cout << input.size() << endl;
    int clusters = 200;
    Clustering *tweetsClustering;
    tweetsClustering = new Clustering(clusters, input, initialization.at(0), assignment.at(0), update.at(0), k, L, metric, size, probes, w);
    tweetsClustering->findClusters();
    //vector<vector<Point*>> final_clusters = tweetsClustering->getClusters();
    map<string,int> which_cluster = tweetsClustering->getWhichCluster();
    delete tweetsClustering;

    vector<Point*> output;
    Point *point;
    for( int i = 0; i < 200; i++ ) {
        point = new Point();
        for( int j = 0; j < 100; j++ ) {
            point->addCoord(0.0);
        }
        output.push_back(point);
    }

    // Compute Sentiments for every cluster
    //vector<Point*> sentiments_clusters;
    Sentiment *tweetsSentiment = new Sentiment(coins_queries, dictionary, 100, input);
    tweetsSentiment->computeTweetSentiment(tweets1, which_cluster, &output);
    delete tweetsSentiment;
    //vector<double> si = tweetsClustering->Silhouette();
    //cout << "Silhouette hoho " << si.at(si.size() - 1) << endl;
    //clustering->print(si, outputFile, myfile, true);
    /*for( int i = 0; i < output.size(); i++ ) {
        output.at(i)->print();
    }*/

    /* LSH using the cluster users - 1B */
    /*vector<tuple<string, vector<string>>> coins_per_user;
    int size1;
    LshRecommend *lshRecommend = new LshRecommend(L, size1, k, output, "cosine", output.size(), output.at(0)->getDimension(), w, P, users);
    coins_per_user = lshRecommend->getRecommendations(coin_names, 2);
    lshRecommend->print(outputFile, "1B");
    delete lshRecommend;
*/



    /* 2B Exercise ! */

    vector<tuple<string, vector<string>>> coins_per_user;
    ClusterRecommend *clusterRecommend = new ClusterRecommend(output, P, initialization.at(0), assignment.at(0), update.at(0), k, L,
                                                              "euclidean", output.size(), probes, w, users);
    coins_per_user = clusterRecommend->getRecommendations(coin_names, 2);
    clusterRecommend->print(outputFile, "2B");
    delete clusterRecommend;

    /* Free memory for the tweets */
    for( int i = 0; i < user_ids.size(); i++ ) {
        for( int j = 0; j < tweets_per_user[user_ids.at(i)].size(); j++ ) {
            delete tweets_per_user[user_ids.at(i)].at(j);
        }
    }

    /* Free memory from tweet vectors */
    for( int i = 0; i < input.size(); i++ ) {
        delete input.at(i);
    }

    free(inputFile); free(outputFile);

    return 1;
}
