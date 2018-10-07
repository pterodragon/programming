#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
struct Input {
  int m;
  int n;
  int N;
  int i;
  int j;
  friend std::ostream &operator<<(std::ostream &s, const Input &x) {
    return s << x.m << ", " << x.n << ", " << x.N << ", " << x.i << ", " << x.j;
  }
};

class Solution {
public:
  int findPaths(int m, int n, int N, int i, int j) {
    // dp[x][y][n] = no of paths to move the ball out of grid boundary at
    // (x, y) with n times of moving
    const int mod = 1000000007;
    vector<vector<int>> dp(m, vector(n, 0));
    for (int a = 0; a < N; ++a) {
      vector<vector<int>> t(m, vector(n, 0));
      for (int x = 0; x < m; ++x) {
        for (int y = 0; y < n; ++y) {
          if (x > 0)
            t[x][y] += dp[x - 1][y] % mod;
          t[x][y] %= mod;
          if (y > 0)
            t[x][y] += dp[x][y - 1] % mod;
          t[x][y] %= mod;
          if (x < m - 1)
            t[x][y] += dp[x + 1][y] % mod;
          t[x][y] %= mod;
          if (y < n - 1)
            t[x][y] += dp[x][y + 1] % mod;
          t[x][y] %= mod;
        }
      }
      for (int x = 0; x < m; ++x) {
        for (int y = 0; y < n; ++y) {
          dp[x][y] =
              t[x][y] + (x == 0) + (y == 0) + (x == m - 1) + (y == n - 1);
          dp[x][y] %= mod;
        }
      }
    }
    return dp[i][j];
  }
};

#endif /* SOLUTION_HPP */
