#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "IOutils.h"

int main(int argc, char* argv[]) {
  /* Read the input file */
  readInput("dataset1.txt", '\n', '\t');
  return 1;
}
