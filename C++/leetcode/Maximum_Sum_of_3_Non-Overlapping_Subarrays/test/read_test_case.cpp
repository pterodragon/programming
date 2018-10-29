#include <fstream>
#include <stdexcept>
#include <vector>

#include "read_test_case.hpp"

vector<int> read_vector(ifstream &file) {
  if (file.get() != '[')
    throw ParseError("missing '['");
  if (file.peek() == ']')
    return {};
  vector<int> vec;
  char c;
  int x;
  do {
    if (!(file >> x))
      throw ParseError("not integer in list");
    vec.push_back(x);
    c = file.get();
  } while (c == ',');
  if (c != ']')
    throw ParseError("missing ']' or not ','");
  return vec;
}

Input read_input(const char *filepath) {
  ifstream file(filepath);
  Input input;
  input.arr = read_vector(file);
  if (file.get() != ',')
    throw ParseError("missing ','");
  file >> input.k;
  return input;
}

vector<int> read_output(const char *filepath) {
  ifstream file(filepath);
  return read_vector(file);
}
