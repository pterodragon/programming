#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool canCross(vector<int>& A) {
    const int N = A.size();
    vector<vector<int>> dp(N, vector<int>(N + 1));
    dp[0][0] = 1;
    for (int q = 1; q < N; ++q) {
      for (int a = 0; a < q; ++a) {
        int dist = A[q] - A[a];
        if (dist < N && !dp[q][dist]) {
          dp[q][dist] |= dp[a][dist - 1] || dp[a][dist] || dp[a][dist + 1];
        }
      }
    }
    return any_of(begin(dp[N - 1]), end(dp[N - 1]), [](bool v) { return v; });
  }
};

#endif /* SOLUTION_HPP */
