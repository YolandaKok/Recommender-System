#include <gtest/gtest.h>
#include "Sentiment.h"
#include <vector>
#include <string>
using namespace std;

TEST( SentimentTest, testUserSentiment ) {

    Sentiment sentiment;
    double expectedResult = 0.318210;
    double actualResult = sentiment.normalizeSi(1.3, 15.0);

    EXPECT_NEAR ( expectedResult, actualResult , 0.00002);
}

TEST( SentimentTest, testUserSentimentNegative ) {

    Sentiment sentiment;
    double expectedResult = -0.318210;
    double actualResult = sentiment.normalizeSi(-1.3, 15.0);

    EXPECT_NEAR ( expectedResult, actualResult , 0.00002);
}