#ifndef __KNN__
#define __KNN__
#include <vector>
#include "Point.h"
#include <fstream>

using namespace std;

double ExactKNN(Point* p, vector<Point*> input, ofstream& output);

#endif
