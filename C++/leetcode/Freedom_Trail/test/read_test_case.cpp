#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "read_test_case.hpp"

std::string read_quoted_string(const std::string &str) {
  if (str.empty() || str[0] != '"' || str.back() != '"') {
    throw std::invalid_argument("first char or last char not '\"'");
  }
  std::string copy = str;
  copy.erase(copy.begin());   // remove '['
  copy.erase(copy.end() - 1); // remove ']'
  return copy;
}

std::pair<std::string, std::string> read_input(const char *filepath) {
  ifstream file(filepath);
  std::string line;
  std::getline(file, line);
  auto first_str = read_quoted_string(line);
  std::getline(file, line);
  auto second_str = read_quoted_string(line);
  return {first_str, second_str};
}

int read_output(const char *filepath) {
  ifstream file(filepath);
  int x;
  file >> x;
  return x;
}
