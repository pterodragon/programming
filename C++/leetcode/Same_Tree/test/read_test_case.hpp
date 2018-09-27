#ifndef READ_TEST_CASE_HPP
#define READ_TEST_CASE_HPP

#include <exception>
#include <iostream>
#include <utility>
#include <vector>

#include "solution.hpp"
using namespace std;

using ParseError = std::invalid_argument;

std::ostream &operator<<(std::ostream &os, TreeNode *node);
std::pair<TreeNode *, TreeNode *> read_input(const char *filepath);
int read_output(const char *filepath);

#endif /* READ_TEST_CASE_HPP */
