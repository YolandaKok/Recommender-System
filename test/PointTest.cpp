#include <gtest/gtest.h>
#include "Sentiment.h"
#include "Point.h"
#include <vector>
#include <random>
#include <string>
using namespace std;

TEST( pointTest, testEuclideanSimilarity ) {
    Point *point1, *point2;
    point1 = new Point();
    point2 = new Point();
    double coord = 1.1;
    double coord2 = 2.1;
    for( int i = 0; i < 9; i++ ) {
      point1->addCoord(coord);
      point2->addCoord(coord2);
      coord += 1.0;
      coord2 += 1.0;
    }

    double expectedResult = 0.25;
    double actualResult = point1->euclidean_similarity(point2);
    delete point1; delete point2;

    EXPECT_EQ ( expectedResult, actualResult);
}
