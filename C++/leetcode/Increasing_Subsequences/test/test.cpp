#define BOOST_TEST_MAIN
#include <boost/functional/hash.hpp>
#include <boost/range/irange.hpp>
#include <boost/test/included/unit_test.hpp>
#include <unordered_set>

#include <prettyprint.hpp>

#include "read_test_case.hpp"
#include "solution.hpp"
#include "test_common.hpp"

template <>
const pretty_print::delimiters_values<char>
    pretty_print::delimiters<std::vector<std::vector<int>>, char>::values = {
        "|| ", " : ", " ||"};

BOOST_DATA_TEST_CASE(test1, (NumberedTestsFromFiles(&read_input, &read_output)),
                     // ^ bdata::make( { 1, 2, 3, 5, 8, 13, 21, 35, 56 } ),
                     test_data) {
  Solution sol;
  std::unordered_set<std::vector<int>, boost::hash<std::vector<int>>>
      set_output;
  std::unordered_set<std::vector<int>, boost::hash<std::vector<int>>>
      set_actual;
  for (const auto &e : test_data.output) {
    set_output.insert(e);
  }
  auto actual =
      sol.findSubsequences(const_cast<vector<int> &>(test_data.input));
  for (const auto &e : actual) {
    set_actual.insert(e);
  }
  BOOST_CHECK_EQUAL(
      actual.size(),
      test_data.output.size()); // test_data.output is unique; actual result
                                // must be unique too
  BOOST_CHECK_EQUAL(set_actual, set_output);
}
