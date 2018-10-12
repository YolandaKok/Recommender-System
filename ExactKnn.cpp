#include "ExactKnn.h"
#include "Point.h"
#include <map>
#include <tuple>
#include <vector>
#include <utility>


using namespace std;

double ExactKNN(Point* p, vector<Point*> input) {
  double distance;
  /* Make a vector with a fixed size */
  map<int, double> mapKnn;
  /* Calculate the distance between two points for every point */
  for( int i = 0; i < input.size(); i++ ) {
    distance = p->euclidean(input.at(i));
    mapKnn.insert(pair<int,double>(p->getId(), distance));
  }
  /* Find the min value */
}
