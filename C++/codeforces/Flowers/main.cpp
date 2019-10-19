#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
  int t, k;
  const int n = 100000;
  const int mod = 1000000007;
  cin >> t >> k;
  vector<int> dp(n + 1, 1);
  dp[0] = 0;
  dp[k] = 2;
  for (int a = k; a < n; ++a) {
    dp[a + 1] = (dp[a] + dp[a - k + 1]) % mod;
  }
  partial_sum(begin(dp), end(dp), begin(dp),
              [](auto x, auto y) { return (x + y) % mod; });
  while (t-- > 0) {
    int a, b;
    cin >> a >> b;
    cout << (mod + dp[b] - dp[a - 1]) % mod << '\n';
  }
}
