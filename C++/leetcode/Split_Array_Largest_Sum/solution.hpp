#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <array>
#include <cstring>
#include <numeric>
#include <vector>

using namespace std;
using P = array<long, 2>;

class Solution {
public:
  int splitArray(vector<int> &nums, int m) {
    const int N = nums.size();
    if (N == 0)
      return 0;
    long inf;
    memset(&inf, 0x3f, sizeof inf);
    vector<vector<P>> dp(N, vector<P>(m, {inf, inf}));
    auto ps = [&dp, &nums](int i, int j) {
      return dp[j][0][0] - dp[i][0][0] + nums[i];
    }; // partial sum inclusive
    int sum = 0;
    for (int a = 0; a < N; ++a) {
      sum += nums[a];
      dp[a][0] = {sum, sum};
    }
    for (int q = 1; q < m; ++q) {
      dp[0][q] = {nums[0], nums[0]};
    }
    for (int q = 1; q < m; ++q) {
      for (int a = q; a < N; ++a) {
        for (int w = 1; w < a + 1; ++w) {
          dp[a][q] = min(dp[a][q], {max(dp[a - w][q - 1][0], ps(a - w + 1, a)),
                                    ps(a - w + 1, a)});
        }
      }
    }
    return dp[N - 1][m - 1][0];
  }
};

#endif /* SOLUTION_HPP */
