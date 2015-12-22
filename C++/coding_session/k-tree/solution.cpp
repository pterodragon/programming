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
//	printf("%d%d%d\n", n, k, d);
	int dp[n + 1][2] = {};
	dp[0][0] = 1;
	for (int i = 1; i < n + 1; i++) {
		for (int j = max(0, i - (d - 1)); j < i; j++) {
			dp[i][0] += dp[j][0];
			dp[i][1] += dp[j][0];
			dp[i][0] %= m;
			dp[i][1] %= m;
		}
		for (int j = max(0, i - k); j < max(0, i - (d - 1)); j++) {
			dp[i][1] += dp[j][1];
			dp[i][1] += dp[j][0];
			dp[i][1] %= m;
		}
	}
	for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < 2; j++) {
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}
	cout << dp[n][1] << endl;

	return 0;
}
