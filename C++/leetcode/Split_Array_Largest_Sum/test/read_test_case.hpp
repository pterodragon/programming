#ifndef READ_TEST_CASE_HPP
#define READ_TEST_CASE_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

#include "prettyprint.hpp"

using namespace std;

struct Input {
  vector<int> arr;
  int m;
  friend ostream& operator<<(ostream& os, const Input& input) {
    return os << '(' << input.arr << ", " << input.m << ')';
  }
};


using ParseError = std::invalid_argument;

Input read_input(const char *filepath);
int read_output(const char *filepath);

#endif /* READ_TEST_CASE_HPP */
