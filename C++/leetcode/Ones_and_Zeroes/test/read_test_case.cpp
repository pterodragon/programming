#include <fstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "read_test_case.hpp"

std::vector<std::string> read_vector_of_string(std::string &str) {
  str.erase(std::remove(str.begin(), str.end(), ' '),
            str.end()); // erase all spaces // maybe bad for some situation
  if (str.empty() || str[0] != '[' || str.back() != ']') {
    throw std::invalid_argument("first char not '[' or last char not ']'");
  }
  std::vector<std::string> res;
  if (str.size() == 2) {
    return res;
  }
  str.erase(str.begin());   // remove '['
  str.erase(str.end() - 1); // remove ']'
  std::vector<std::string> strs;
  boost::split(strs, str, boost::is_any_of(","));
  for (auto &e : strs) {
    if (e.size() < 2 || e[0] != '"' || e.back() != '"') {
      throw std::invalid_argument("first char not '[' or last char not ']'");
    }
    res.push_back(e.substr(1, e.size() - 2));
  }
  return res;
}

std::tuple<std::vector<std::string>, int, int>
read_input(const char *filepath) {
  ifstream file(filepath);
  std::string line;
  std::getline(file, line);
  int x;
  int y;
  file >> x;
  file >> y;
  return std::make_tuple(read_vector_of_string(line), x, y);
}

int read_output(const char *filepath) {
  ifstream file(filepath);
  int x;
  file >> x;
  return x;
}
