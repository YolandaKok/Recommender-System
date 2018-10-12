#include "ExactKnn.h"
#include "Point.h"
#include <map>
#include <tuple>
#include <vector>
#include <utility>


using namespace std;

double ExactKNN(Point* p, vector<Point*> input) {
  double distance, final_distance;
  int id = 0;
  /* Initialize time */

  /* Make a vector with a fixed size */
  //map<int, double> mapKnn;
  final_distance = p->euclidean(input.at(0));
  /* Calculate the distance between two points for every point */
  for( int i = 0; i < input.size(); i++ ) {
    distance = p->euclidean(input.at(i));
    if(distance < final_distance) {
      final_distance = distance;
      id = input.at(i)->getId();
    }
    //mapKnn.insert(pair<int,double>(p->getId(), distance));
  }

  /* Calculate the time in seconds */

}
