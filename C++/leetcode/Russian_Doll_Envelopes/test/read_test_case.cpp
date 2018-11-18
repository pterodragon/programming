#include <fstream>
#include <stdexcept>
#include <vector>

#include "read_test_case.hpp"

template <typename T>
T read_element(ifstream& file);

template <>
pair<int, int> read_element<pair<int, int>>(ifstream& file) {
  if (file.get() != '[') throw ParseError("missing '['");
  int x, y;
  if (!(file >> x)) throw ParseError("can't read element in pair");
  if (file.get() != ',') throw ParseError("missing ','");
  if (!(file >> y)) throw ParseError("can't read element in pair");
  if (file.get() != ']') throw ParseError("missing ']'");
  return {x, y};
}

template <typename T>
vector<T> read_vector(ifstream& file) {
  if (file.get() != '[') throw ParseError("missing '['");
  if (file.peek() == ']') return {};
  vector<T> vec;
  char c;
  do {
    vec.push_back(read_element<T>(file));
    c = file.get();
  } while (c == ',');
  if (c != ']') throw ParseError("missing ']' or not ','");
  return vec;
}

vector<pair<int, int>> read_input(const char* filepath) {
  ifstream file(filepath);
  return read_vector<pair<int, int>>(file);
}

int read_output(const char* filepath) {
  ifstream file(filepath);
  int x;
  file >> x;
  return x;
}
