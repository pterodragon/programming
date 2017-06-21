#ifndef READ_TEST_CASE_HPP
#define READ_TEST_CASE_HPP 

#include <vector>
#include <iostream>

#include "solution.hpp"
using namespace std;

std::pair<std::string, std::string> read_input(const char* filepath);
int read_output(const char* filepath);

#endif /* READ_TEST_CASE_HPP */