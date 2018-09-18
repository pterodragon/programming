#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "read_test_case.hpp"

std::vector<int> read_vector(std::string &str) {
  str.erase(std::remove(str.begin(), str.end(), ' '),
            str.end()); // erase all spaces
  if (str.empty() || str[0] != '[' || str.back() != ']') {
    throw std::invalid_argument("first char not '[' or last char not ']'");
  }
  if (str.size() == 2) {
    return std::vector<int>();
  }
  str.erase(str.begin());   // remove '['
  str.erase(str.end() - 1); // remove ']'
  std::vector<std::string> strs;
  boost::split(strs, str, boost::is_any_of(","));
  std::vector<int> res;
  for (auto &e : strs) {
    int val = boost::lexical_cast<int>(e);
    res.push_back(val);
  }
  return res;
}

std::vector<int> read_input(const char *filepath) {
  ifstream file(filepath);
  std::string line;
  std::getline(file, line);
  return read_vector(line);
}

int read_output(const char *filepath) {
  ifstream file(filepath);
  int x;
  file >> x;
  return x;
}
