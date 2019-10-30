#include "solution.hpp"
#include <algorithm>
#include <iostream>
#include <string.h>

using namespace std;

// // Sol 1A
// // backward dp
// // enumerating items from beginning (z = 0..N-1)
// // inner loop is looping items
//
// // items are 0 indexed, 0..N-1'th items
// // dp[a][b] = solution for a knapsack of weight a,
// // only can use items until and including b'th item
// long long solve(int N, int W, int *v, int *w, long long dp[MAX_W][MAX_N]) {
//   for (int q = 1; q < W + 1; ++q) {
//     for (int z = 0; z < N; ++z) {
//       dp[q][z] = max(               //
//           z > 0 ? dp[q][z - 1] : 0, //
//           q - w[z] >= 0 ?           //
//               (v[z] + (z > 0 ? dp[q - w[z]][z - 1] : 0))
//                         : 0);
//     }
//   }
//  
//   return dp[W][N - 1];
// }

// // Sol 2A
// // forward dp
// // enumerating items from beginning (z = 0..N)
// // inner loop is looping items
//
// // items are 0 indexed, 0..N-1'th items
// // dp[a][b] = solution for a knapsack of weight a,
// // only can use items until and excluding b'th item
// long long solve(int N, int W, int *v, int *w, long long dp[MAX_W][MAX_N]) {
//   for (int q = 0; q < W; ++q) {
//     for (int z = 0; z < N; ++z) {
//       dp[q + 1][z + 1] = max( //
//           dp[q + 1][z],       //
//           q + 1 - w[z] >= 0 ?     //
//               (v[z] + dp[q + 1 - w[z]][z])
//                         : 0);
//     }
//   }
//   return dp[W][N];
// }

// // Sol 3A
// // forward dp
// // enumerating items from beginning (z = 0..N)
// // inner loop is looping
// // "weights >= the current item weight"
// // in descending order
//
// // items are 0 indexed, 0..N-1'th items
// // dp[a][b] = solution for a knapsack of weight a,
// // only can use items until and including b'th item
// long long solve(int N, int W, int *v, int *w, long long dp[MAX_W][MAX_N]) {
// 
//   for (int z = 0; z < N; ++z) {
//     for (int q = W - w[z]; q >= 0; --q) {
//       dp[q + w[z]][z] = max(dp[q + w[z]][z], v[z] + dp[q][z]);
//     }
//     for (int q = 0; q < W + 1; ++q) {
//       dp[q][z + 1] = dp[q][z];
//     }
//   }
// 
//   return dp[W][N - 1];
// }

// // Sol 3B
// // forward dp
// // enumerating items from beginning (z = 0..N)
// // inner loop is looping
// // "weights >= the current item weight"
// // in descending order
// //
// // items are 0 indexed, 0..N-1'th items
// // dp[a][b] = solution for a knapsack of weight a,
// // only can use items until and including b'th item
// long long solve(int N, int W, int *v, int *w, long long dp[MAX_W][MAX_N]) {
//   for (int z = 0; z < N; ++z) {
//     for (int q = W - w[z]; q >= 0; --q) {
//       dp[q + w[z]][0] = max(dp[q + w[z]][0], v[z] + dp[q][0]);
//     }
//   }
//   return dp[W][0];
// }
