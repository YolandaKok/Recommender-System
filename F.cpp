#include "F.h"
#include "H.h"
#include <math.h>
#include <random>
#include <iostream>

using namespace std;

F::F(int k) {
  /* Initialize the h functions */
  //this->h_functions = h_functions;
  this->h_functions = (H**) malloc(sizeof(H*) * k);
  /*for( int i = 0; i < k; i++ ) {
    this->h_functions[i] = new H(128, 4, 0.0, 1.0);
  }*/
  this->k = k;
  //generateRk();
}

int F::getK() {
  return this->k;
}

H* F::getH(int i) {
  return this->h_functions[i];
}

void F::setH(H* h, int i) {
  this->h_functions[i] = h;
}

/*void F::generateRk() {
  int i;
  random_device rd;  //Will be used to obtain a seed for the random number engine
  default_random_engine generator(rd());
  normal_distribution<double> distribution(0.0, 1.0);
  double number;
  this->Rk = (int*) malloc(sizeof(int) * k);
  for(i = 0; i < this->k; i++)
    this->Rk[i] = abs(floor(distribution(generator)));
}*/

int F::hashForPoint(Point* p) {

}

/*void F::printRk() {
  for( int i = 0; i < this->k; i++ )
    cout << this->Rk[i] << " ";
  cout << endl;
}*/

/*Point* F::getV() {
  return this->h_functions[1]->getV();
}*/

F::~F() {
  cout << "Deleted F function" << endl;
}
