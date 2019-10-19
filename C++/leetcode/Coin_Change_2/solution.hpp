#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

class Solution {
public:
  int change(int N, vector<int> &C) {
    // column by column update (columns: coin denomination sorted)
    sort(begin(C), end(C));
    const int M = C.size();

    int dp[N][M];
    memset(dp, 0, N * M * sizeof(int));
    for (int w = 0; w < M; ++w) {
      if (w < N) dp[w][w] = 1;
    }
    for (int q = 0; q < N; ++q) {
      for (int w = 0; w < M; ++w) {
         cout << dp[q][w] << ", ";
      }
      cout << '\n';
    }
    return 42;
  }
};

#endif /* SOLUTION_HPP */
