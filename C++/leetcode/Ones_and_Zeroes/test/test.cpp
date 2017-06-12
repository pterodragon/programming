#define BOOST_TEST_MODULE "Ones_and_Zeroes"
#include <tuple>
#include <boost/test/included/unit_test.hpp>

#include <prettyprint.hpp>

#include "test_common.hpp"
#include "read_test_case.hpp"
#include "solution.hpp"

template<> const pretty_print::delimiters_values<char> pretty_print::delimiters<std::vector<std::vector<int>>, char>::values = { "|| ", " : ", " ||" };

BOOST_DATA_TEST_CASE(
        test1,
        (make_tests(&read_input, &read_output)),
        // ^ bdata::make( { 1, 2, 3, 5, 8, 13, 21, 35, 56 } ),
        test_data)
{
    Solution sol;
    auto input = test_data.input;
    auto actual = sol.findMaxForm(std::get<0>(input), std::get<1>(input), std::get<2>(input));
    BOOST_CHECK_EQUAL(actual, test_data.output);
}