#include <fstream>
#include <vector>

#include "read_test_case.hpp"

using namespace std;
vector<vector<char>> read_input(const char *filepath) {
  ifstream file(filepath);
  string str;
  vector<vector<char>> result;
  while (getline(file, str)) {
    result.push_back(vector<char>(str.begin(), str.end()));
  }
  return result;
}

int read_output(const char *filepath) {
  ifstream file(filepath);
  int result;
  file >> result;
  return result;
}
