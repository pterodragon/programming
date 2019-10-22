#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <algorithm>
#include <tuple>

using namespace std;

// void solve(int n, int c, int *a, int *b, int *out) {
//   int dp[n][2]; // (x, 0) previously taking stairs till level x
//   dp[0][0] = 0;
//   dp[0][1] = 0x3f3f3f3f; // inf
//   out[0] = 0;
//   for (int q = 1; q < n; ++q) {
//     dp[q][0] = min(dp[q - 1][0] + a[q - 1], dp[q - 1][1] + a[q - 1]);
//     dp[q][1] = min(dp[q - 1][0] + b[q - 1] + c, dp[q - 1][1] + b[q - 1]);
//     out[q] = min(dp[q][0], dp[q][1]);
//   }
// }

// void solve(int n, int c, int *a, int *b, int *out) {
//   int dp[n][2]; // (x, 0) previously taking stairs till level x
//   dp[0][0] = 0;
//   dp[0][1] = 0x3f3f3f3f; // inf
//   out[0] = 0;
//   for (int q = 0; q < n - 1; ++q) {
//     dp[q + 1][0] = min(dp[q][0], dp[q][1]) + a[q];
//     dp[q + 1][1] = min(dp[q][0] + b[q] + c, dp[q][1] + b[q]);
//     out[q + 1] = min(dp[q + 1][0], dp[q + 1][1]);
//   }
// }

void solve(int n, int c, int *a, int *b, int *out) {
  int z0 = 0, z1 = 0x3f3f3f3f;
  out[0] = 0;
  for (int q = 0; q < n - 1; ++q) {
    tie(z0, z1) = pair{min(z0, z1) + a[q], min(z0 + c, z1) + b[q]};
    out[q + 1] = min(z0, z1);
  }
}
#endif /* SOLUTION_HPP */
