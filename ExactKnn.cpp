#include "ExactKnn.h"
#include "Point.h"
#include <map>
#include <tuple>
#include <vector>
#include <utility>
#include <ctime>
#include <iostream>

using namespace std;

double ExactKNN(Point* p, vector<Point*> input) {
  double distance, final_distance;
  int id = 0;
  /* Initialize time */
  const clock_t begin_time = clock();
  clock_t interval;
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
  cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC << " time" << endl;
  cout << final_distance << endl;
  cout << id << endl;
}
