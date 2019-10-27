#include "solution.hpp"
#include <iostream>

using namespace std;

int main() {
  int N, W;
  cin >> N >> W;
  int v[N], w[N];
  for (int q = 0; q < N; ++q)
    cin >> w[q] >> v[q];
 
  long long ans = solve(N, W, v, w);
  cout << ans << '\n';
}
