#include <gtest/gtest.h>
#include "Sentiment.h"
#include <vector>
#include <random>
#include <string>
using namespace std;

random_device rd;
mt19937 gen(rd());

default_random_engine generator(rd());

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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
