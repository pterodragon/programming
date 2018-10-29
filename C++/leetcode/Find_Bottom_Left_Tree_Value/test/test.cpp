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

auto x = NumberedTestsFromFiles(&read_input, &read_output);

BOOST_DATA_TEST_CASE(test1, x,
                     // ^ bdata::make( { 1, 2, 3, 5, 8, 13, 21, 35, 56 } ),
                     test_data) {
  Solution sol;
  int actual = sol.findBottomLeftValue(test_data.input);
  BOOST_CHECK_EQUAL(actual, test_data.output);
}
