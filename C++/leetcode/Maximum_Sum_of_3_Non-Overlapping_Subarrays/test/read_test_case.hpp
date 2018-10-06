#ifndef READ_TEST_CASE_HPP
#define READ_TEST_CASE_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

#include "prettyprint.hpp"
#include "solution.hpp"

using namespace std;

struct Input {
  vector<int> arr;
  int k;
  friend ostream& operator<<(ostream& os, const Input& input) {
    return os << '(' << input.arr << ", " << input.k << ')';
  }
};


using ParseError = std::invalid_argument;

Input read_input(const char *filepath);
vector<int> read_output(const char *filepath);

#endif /* READ_TEST_CASE_HPP */
