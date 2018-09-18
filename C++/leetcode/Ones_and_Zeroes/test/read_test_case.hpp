#ifndef READ_TEST_CASE_HPP
#define READ_TEST_CASE_HPP

#include <iostream>
#include <vector>

#include "solution.hpp"
using namespace std;

std::tuple<std::vector<std::string>, int, int> read_input(const char *filepath);
int read_output(const char *filepath);

#endif /* READ_TEST_CASE_HPP */
