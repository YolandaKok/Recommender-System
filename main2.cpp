#include <iostream>
#include "Hypercube.h"

using namespace std;

int main(int argc, char* argv[]) {
  Hypercube *hypercube = new Hypercube();
  cout << hypercube->getSize() << endl;
  Point* p = new Point();
  p->addCoord(10);
  p->addCoord(43);
  p->addCoord(3.3);
  cout << hypercube->insert(p) << endl;
  return 1;
}
