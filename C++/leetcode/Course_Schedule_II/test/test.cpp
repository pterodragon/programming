#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <iostream>

#include <prettyprint.hpp>

#include "read_test_case.hpp"
#include "solution.hpp"
#include "test_common.hpp"

template <>
const pretty_print::delimiters_values<char>
    pretty_print::delimiters<std::vector<std::pair<int, int>>, char>::values = {
        "|| ", " : ", " ||"};

bool check_actual(int numCourses, const vector<pair<int, int>>& prerequisites, const vector<int>& actual) {
    if (numCourses != actual.size()) return false;
    struct deg_prop {
        int in_degree = 0;
        int out_degree = 0;
    };
    vector<vector<int>> adj_list(numCourses, vector<int>());
    vector<deg_prop> deg(numCourses);
    for (auto p : prerequisites) {
        adj_list[p.second].push_back(p.first);
        ++deg[p.first].in_degree;
        ++deg[p.second].out_degree;
    }
    for (auto c: actual) {
        if (deg[c].in_degree != 0) return false;
        for (auto nei: adj_list[c]) {
            --deg[nei].in_degree;
        }
    }
    return true;
}

BOOST_DATA_TEST_CASE(test1, (NumberedTestsFromFiles(&read_input, &read_output)),
                     // ^ bdata::make( { 1, 2, 3, 5, 8, 13, 21, 35, 56 } ),
                     test_data) {
  Solution sol;
  auto actual = sol.findOrder(test_data.input.nCourses, const_cast<Input::PrereqPairs&>(test_data.input.prereqPairs));
  // BOOST_CHECK_EQUAL(actual, test_data.output);
  BOOST_CHECK(check_actual(test_data.input.nCourses, test_data.input.prereqPairs, actual));
}
