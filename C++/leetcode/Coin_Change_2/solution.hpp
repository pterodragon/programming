#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int change(int N, vector<int> &C) {
    // column by column update (columns: coin denomination sorted)
    sort(begin(C), end(C));
    const int M = C.size();
    if (M == 0)
      return N == 0 ? 1 : 0;
    ++N;

    int dp[N][M];
    memset(dp, 0, N * M * sizeof(int));
    dp[0][0] = 1;

    // Forward DP method
    for (int q = 0; q < N; ++q) {
      for (int w = 0; w < M; ++w) {
        if (int z = q + C[w]; z < N)
          dp[z][w] += dp[q][w];

        if (w < M - 1)
          dp[q][w + 1] += dp[q][w];
      }
    }
    return dp[N - 1][M - 1];
  }
};

#endif /* SOLUTION_HPP */
