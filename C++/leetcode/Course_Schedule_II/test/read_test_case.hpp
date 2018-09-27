#ifndef READ_TEST_CASE_HPP
#define READ_TEST_CASE_HPP

#include <iostream>
#include <utility>
#include <vector>

#include <prettyprint.hpp>

struct Input {
  int nCourses;
  using PrereqPair = std::pair<int, int>;
  using PrereqPairs = std::vector<PrereqPair>;
  PrereqPairs prereqPairs;
  friend std::ostream &operator<<(std::ostream &o, const Input &i) {
    return o << "{{" << i.nCourses << ", " << i.prereqPairs << "}}";
  }
};

Input read_input(const char *filepath);
std::vector<int> read_output(const char *filepath);

#endif /* READ_TEST_CASE_HPP */
