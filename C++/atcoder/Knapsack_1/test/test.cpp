#define CATCH_CONFIG_MAIN

#include "solution.hpp"
#include <catch2/catch.hpp>
#include <tuple>
#include "prettyprint.hpp"
#include <vector>

using namespace std;
long long dp[MAX_W][MAX_N];

TEST_CASE("test_solution", "[knapsack_1]") {
  for (auto &v_ : {
           tuple<int, int, vector<int>, vector<int>, int> //
           {6, 15, {6,5,6,6,3,7}, {5,6,4,6,5,2}, 17},
       }) {
    auto [N, W, w, v, exp] = v_;
    auto res = solve(N, W, v.data(), w.data(), dp);
    INFO("N = " << N << ", W = " << W << ", v = " << v << ", w = " << w );
    REQUIRE(res == exp);
    memset(dp, 0, sizeof(long long) * MAX_W * MAX_N); // reset
  }
}
