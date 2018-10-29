#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> maxSumOfThreeSubarrays(vector<int> &nums, int k) {
    auto arrsum = [&nums](int a, int b) {
      return accumulate(begin(nums) + a, begin(nums) + b, 0);
    };
    const int N = nums.size();
    const int inf = 0x3f3f3f3f;
    vector<vector<int>> dp(3, vector<int>(N, -inf));
    for (int t = 0; t < 3; ++t) {
      int start = (t + 1) * k - 1;
      for (int a = start; a < N; ++a) {
        // 'a' is the index where the new subarray may end
        // max sum when array is placed ending with index a; still ok event if
        // it's some -inf + sth
        int max_end_here =
            arrsum(a - k + 1, a + 1) + (t > 0 ? dp[t - 1][a - k] : -inf);
        int prev = a > start ? dp[t][a - 1] : -inf;
        dp[t][a] = max({dp[t][a], max_end_here, prev});
      }
    }
    int ans[4] = {N, N, N, N - 1 + k};
    for (int t = 2; t >= 0; --t) {
      auto it = max_element(begin(dp[t]), begin(dp[t]) + ans[t + 1] - k + 1);
      ans[t] = distance(begin(dp[t]), it);
    }
    return {ans[0] - k + 1, ans[1] - k + 1, ans[2] - k + 1};
  }
};

#endif /* SOLUTION_HPP */
