#include <fstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "read_test_case.hpp"

Input read_input(const char *filepath) {
  ifstream file(filepath);
  Input input;
  file >> input.m;
  file >> input.n;
  file >> input.N;
  file >> input.i;
  file >> input.j;
  return input;
}

int read_output(const char *filepath) {
  ifstream file(filepath);
  int x;
  file >> x;
  return x;
}
