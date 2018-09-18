#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <string>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
  pair<int, int> zero_one_count(const string &s) {
    int zeros = 0;
    int ones = 0;
    for (char c : s) {
      if (c == '0')
        ++zeros;
      if (c == '1')
        ++ones;
    }
    return {zeros, ones};
  }
  int findMaxForm(const vector<string> &strs, int m, int n) {
    const size_t L = strs.size();
    vector<pair<int, int>> counts;
    counts.push_back({1 << 31, 1 << 31}); // dummy
    for (const auto &s : strs) {
      counts.push_back(zero_one_count(s));
    }
    int dp[2][m + 1][n + 1]; // d1: look at items [0, x]; first items is 1th //
                             // 0th is dummy
    for (size_t x = 0; x < L + 1; ++x) {
      for (int y = 0; y < m + 1; ++y) {
        for (int z = 0; z < n + 1; ++z) {
          bool x_ = x % 2;
          if (x == 0) {
            dp[x_][y][z] = 0;
          } else {
            const int c0 =
                counts[x].first; // due to the dummy, items is now 1 indexed
            const int c1 = counts[x].second;
            dp[x_][y][z] = dp[1 - x_][y][z];
            if (y >= c0 && z >= c1) { // enough
              dp[x_][y][z] = max(dp[x_][y][z], dp[1 - x_][y - c0][z - c1] + 1);
            }
          }
        }
      }
    }
    return dp[L % 2][m][n];
  }
};

#endif /* SOLUTION_HPP */
