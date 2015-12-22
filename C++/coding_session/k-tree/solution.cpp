#include <bits/stdc++.h>
using namespace std;

int main() {
	constexpr int m = 1000000007;
	int n, k, d;
	scanf("%d%d%d", &n, &k, &d);
	if (d > k) {
		cout << 0 << endl;
		return 0;
	}
	long long dp[n + 1][2] = {};
	dp[0][0] = 1;
	for (int i = 1; i < n + 1; i++) {
		for (int j = max(0, i - (d - 1)); j < i; j++) {
			dp[i][0] += (dp[j][0] % m);
			dp[i][1] += (dp[j][1] % m);
			dp[i][0] %= m;
			dp[i][1] %= m;
		}
		for (int j = max(0, i - k); j < max(0, i - (d - 1)); j++) {
			dp[i][1] += (dp[j][1] % m + dp[j][0] % m);
			dp[i][1] %= m;
		}
	}
	cout << dp[n][1] << endl;

	return 0;
}
