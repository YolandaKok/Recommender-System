#include <iostream>
#include <fstream>
#include <string>
#include "Point.h"
#include <stdlib.h>
#include <vector>

using namespace std;

vector<Point*> readFile(char* file, double& R) {
  string line;
  ifstream myfile (file);
  string delimiter = " ";
  string token;
  size_t pos = 0;
  size_t sz;
  string str1 ("Radius:");
  vector<Point*> points;
  int count = 0;
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      Point *point = new Point();
      while ((pos = line.find(delimiter)) != string::npos) {
        token = line.substr(0, pos);
        if(token.compare(str1) == 0) {
          line.erase(0, pos + delimiter.length());
          token = line.substr(0, pos);
          R = stod(token, &sz);
          cout << R << endl;
        }
        else {
          line.erase(0, pos + delimiter.length());
          if(count == 0) {
            point->setId(stoi(token));
          }
          else {
            //cout << token << endl;;
            point->addCoord(stod(token, &sz));
          }
          count++;
          if(count == 128) {
            //line.erase(0, pos + delimiter.length());
            token = line.substr(0, pos);
            point->addCoord(stod(token, &sz));
          }
        }
      }
      points.push_back(point);
      count = 0;
    }
    cout << points.at(1)->getId() << endl;
    points.at(1)->print();
    cout << points.at(1)->getDimension() << endl;
    myfile.close();
  }
  return points;
}
