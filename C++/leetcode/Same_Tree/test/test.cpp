#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>

#include "read_test_case.hpp"
#include "solution.hpp"
#include "test_common.hpp"

#include <boost/range/irange.hpp>
#include <prettyprint.hpp>

template <>
const pretty_print::delimiters_values<char>
    pretty_print::delimiters<std::vector<std::vector<char>>, char>::values = {
        "||\n ", " :\n ", " \n||"};

BOOST_DATA_TEST_CASE(test1, (NumberedTestsFromFiles(&read_input, &read_output)),
                     // ^ bdata::make( { 1, 2, 3, 5, 8, 13, 21, 35, 56 } ),
                     test_data) {
  Solution sol;
  int actual = sol.isSameTree(test_data.input.first, test_data.input.second);
  BOOST_CHECK_EQUAL(actual, test_data.output);
}
