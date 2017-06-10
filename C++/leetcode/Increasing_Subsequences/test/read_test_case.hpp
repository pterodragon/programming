#ifndef READ_TEST_CASE_HPP
#define READ_TEST_CASE_HPP 

#include <vector>
#include <iostream>

#include "solution.hpp"
using namespace std;

std::vector<int> read_input(const char* filepath);
std::vector<std::vector<int>> read_output(const char* filepath);

#endif /* READ_TEST_CASE_HPP */