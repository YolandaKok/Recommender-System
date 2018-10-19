#include <iostream>
#include "Hypercube.h"

using namespace std;

int main(int argc, char* argv[]) {
  Hypercube *hypercube = new Hypercube();
  Point* p = new Point();
  p->addCoord(10);
  p->addCoord(43);
  p->addCoord(3);
  hypercube->insert_point(p);
  hypercube->findNearest(p);
  return 1;
}
