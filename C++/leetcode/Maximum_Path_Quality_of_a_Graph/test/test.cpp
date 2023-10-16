#define CATCH_CONFIG_MAIN

#include "prettyprint.hpp"
#include "solution.hpp"
#include <catch2/catch.hpp>
#include <tuple>

TEST_CASE("test_solution", "[Maximum_Path_Quality_of_a_Graph]") {
  Solution sol;
  for (auto &v_ : {
           tuple<vector<int>, vector<vector<int>>, int, int>{
               {1, 2, 3, 4},
               {{0, 1, 10}, {1, 2, 11}, {2, 3, 12}, {1, 3, 13}},
               50,
               7},
           {{5, 10, 15, 20}, {{0, 1, 10}, {1, 2, 10}, {0, 3, 10}}, 30, 25},
           {{0, 32, 10, 43}, {{0, 1, 10}, {1, 2, 15}, {0, 3, 10}}, 49, 75},
       }) {
    auto [values, edges, maxtime, exp] = v_;
    auto res = sol.maximalPathQuality(values, edges, maxtime);
    INFO("values = " << values << ", edges = " << edges
                     << ", expected = " << exp);
    REQUIRE(res == exp);
  }
}
