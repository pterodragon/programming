#ifndef READ_TEST_CASE_HPP
#define READ_TEST_CASE_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

#include "prettyprint.hpp"

using namespace std;

using ParseError = std::invalid_argument;

vector<int> read_input(const char *filepath);
bool read_output(const char *filepath);

#endif /* READ_TEST_CASE_HPP */
