#define CATCH_CONFIG_MAIN

#include "prettyprint.hpp"
#include "solution.hpp"
#include <catch2/catch.hpp>
#include <tuple>
#include <vector>

using namespace std;

TEST_CASE("test_solution", "[By_Elevator_or_Stairs]") {
  for (auto [n, c, a, b, exp] :                                //
       {tuple<int, int, vector<int>, vector<int>, vector<int>> //
        {10,
         2,
         {7, 6, 18, 6, 16, 18, 1, 17, 17},
         {6, 9, 3, 10, 9, 1, 10, 1, 5},
         {0, 7, 13, 18, 24, 35, 36, 37, 40, 45}},
        {10,
         1,
         {3, 2, 3, 1, 3, 3, 1, 4, 1},
         {1, 2, 3, 4, 4, 1, 2, 1, 3},
         {0, 2, 4, 7, 8, 11, 13, 14, 16, 17}}}) {
    vector<int> out(n);
    solve(n, c, &a[0], &b[0], &out[0]);
    INFO("exp = " << exp);
    INFO("out = " << out);
    for (int q = 0; q < n; ++q) {
      REQUIRE(out[q] == exp[q]);
    }
  }
}
