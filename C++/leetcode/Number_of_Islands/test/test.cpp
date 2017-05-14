#define BOOST_TEST_MODULE "Number_of_Islands_test"
#include <boost/test/included/unit_test.hpp>

#include "test_common.hpp"
#include "read_test_case.hpp"
#include "solution.hpp"

#include <boost/range/irange.hpp>
#include <prettyprint.hpp>

template<> const pretty_print::delimiters_values<char> pretty_print::delimiters<std::vector<std::vector<char>>, char>::values = { "||\n ", " :\n ", " \n||" };

BOOST_DATA_TEST_CASE(
        test1,
        (make_tests(&read_input, &read_output)),
        // ^ bdata::make( { 1, 2, 3, 5, 8, 13, 21, 35, 56 } ),
        island_map, expected)
{
    auto filepaths = get_all_test_filepaths();
    for (const auto& f : filepaths) {
        cout << f << '\n';
    }
    cout << "island map is " << island_map << '\n';
    Solution sol;
    int actual = sol.numIslands(island_map);
    BOOST_CHECK_EQUAL(actual, expected);
}

//BOOST_AUTO_TEST_CASE(FailTest) {
//    BOOST_FAIL("");
//}
