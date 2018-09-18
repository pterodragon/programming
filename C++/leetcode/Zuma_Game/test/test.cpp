#define BOOST_TEST_MODULE "Zuma_Game"
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
                     test_data) {
  // auto filepaths = get_all_test_filepaths();
  // for (const auto& f : filepaths) {
  //    cout << f << '\n';
  //}
  const std::string board = test_data.input.first;
  const std::string hand = test_data.input.second;
  Solution sol;
  int actual = sol.findMinStep(board, hand);
  BOOST_CHECK_EQUAL(actual, test_data.output);
}
