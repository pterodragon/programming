#ifndef READ_TEST_CASE_HPP
#define READ_TEST_CASE_HPP

#include <iostream>
#include <vector>

#include "solution.hpp"
using namespace std;

std::vector<std::vector<int>> read_input(const char *filepath);
std::vector<std::pair<int, int>> read_output(const char *filepath);
#endif /* READ_TEST_CASE_HPP */
