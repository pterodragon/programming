#define CATCH_CONFIG_MAIN

#include "solution.hpp"
#include <catch2/catch.hpp>
#include <tuple>
#include "prettyprint.hpp"

TEST_CASE("test_solution", "[Coin_Change_2]") {
  Solution sol;
  for (auto &v_ : {
           tuple<vector<int>, int, int> //
           {{2, 3, 5, 6}, 10, 5},
           {{1, 2, 5}, 5, 4},
           {{1, 2, 3}, 3, 3},
           {{1}, 1, 1},
           {{1}, 2, 1},
           {{1}, 1000, 1},
           {{2}, 2, 1},
           {{2}, 20, 1},
           {{2}, 1000, 1},
           {{2}, 1001, 0},
           {{2, 3, 7}, 0, 1},
           {{}, 0, 1},
           {{}, 1, 0},
       }) {
    auto [v, target, exp] = v_;
    auto res = sol.change(target, v);
    INFO("coins = " << v << ", target = " << target << ", expected = " << exp);
    REQUIRE(res == exp);
  }
}
