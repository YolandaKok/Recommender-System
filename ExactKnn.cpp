#include "ExactKnn.h"
#include "Point.h"
#include <map>
#include <tuple>
#include <vector>
#include <utility>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

double ExactKNN(Point* p, vector<Point*> input, ofstream& output) {
  double distance = 0.0, final_distance;
  int id = 0;
  /* Initialize time */
  const clock_t begin_time = clock();
  clock_t interval;
  /* Make a vector with a fixed size */
  //map<int, double> mapKnn;
  final_distance = 10000.0;
  /* Calculate the distance between two points for every point */
  for( int i = 0; i < input.size(); i+=1 ) {
    distance = p->euclidean(input.at(i));
    if(distance < final_distance) {
      final_distance = distance;
      id = input.at(i)->getId();
    }
  }

  /* Calculate the time in seconds */
  cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC << " time" << endl;
  cout << "Final distance" << final_distance << endl;
  cout << id << endl;
  output << "Nearest Neighbor: " << id << endl;
  output << "distanceTrue: " << final_distance << endl;
  output << "tTrue: " << double( clock () - begin_time ) /  CLOCKS_PER_SEC  << endl << endl;
}
