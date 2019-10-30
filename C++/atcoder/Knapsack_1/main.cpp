#include "solution.hpp"
#include <iostream>

using namespace std;
long long dp[MAX_W][MAX_N];

int main() {
  int N, W;
  cin >> N >> W;
  int v[N], w[N];
  for (int q = 0; q < N; ++q)
    cin >> w[q] >> v[q];
 
  long long ans = solve(N, W, v, w, dp);
  cout << ans << '\n';
}
