#ifndef READ_TEST_CASE_HPP
#define READ_TEST_CASE_HPP 

#include <vector>
#include <iostream>
#include <utility>

#include "solution.hpp"
using namespace std;

std::ostream& operator<<(std::ostream& os, TreeNode* node);
std::pair<TreeNode*, TreeNode*> read_input(const char* filepath);
int read_output(const char* filepath);

#endif /* READ_TEST_CASE_HPP */
