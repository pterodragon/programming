#include <fstream>
#include <stdexcept>
#include <vector>

#include "read_test_case.hpp"

vector<int> read_vector(ifstream &file) {
  if (file.get() != '[') throw ParseError("missing '['");
  if (file.peek() == ']') return {};
  vector<int> vec;
  char c;
  int x;
  do {
    if (!(file >> x)) throw ParseError("not integer in list");
    vec.push_back(x);
    c = file.get();
  } while (c == ',');
  if (c != ']') throw ParseError("missing ']' or not ','");
  return vec;
}

std::vector<vector<int>> read_vector_of_vector(ifstream &file) {
  if (file.get() != '[') throw ParseError("missing '['");
  if (file.peek() == ']') return {};
  vector<vector<int>> vvec;
  char c;
  do {
    auto vec = read_vector(file);
    vvec.push_back(vec);
    c = file.get();
  } while (c == ',');
  if (c != ']') throw ParseError("missing ']' or not ','");
  return vvec;
}

Input read_input(const char *filepath) {
  ifstream file(filepath);
  Input input;
  input.m = read_vector_of_vector(file);
  file >> input.k;
  return input;
}

int read_output(const char *filepath) {
  ifstream file(filepath);
  int x;
  file >> x;
  return x;
}
