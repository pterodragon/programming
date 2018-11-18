#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <tuple>

#include <prettyprint.hpp>

#include "read_test_case.hpp"
#include "solution.hpp"
#include "test_common.hpp"

template <>
const pretty_print::delimiters_values<char>
    pretty_print::delimiters<std::vector<std::vector<int>>, char>::values = {
        "|| ", " : ", " ||"};

auto x = NumberedTestsFromFiles(&read_input, &read_output);

BOOST_DATA_TEST_CASE(test1, x, test_data) {
  Solution sol;
  auto input = test_data.input;
  auto actual = sol.maxSumSubmatrix(const_cast<vector<vector<int>>&>(input.m), input.k);
  BOOST_CHECK_EQUAL(actual, test_data.output);
}
