#include <iostream>
#include "Hypercube.h"

using namespace std;

int main(int argc, char* argv[]) {
  Hypercube *hypercube = new Hypercube();
  cout << hypercube->getSize() << endl;
  return 1;
}
