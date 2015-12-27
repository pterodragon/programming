#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	/**
	 * @param prices: Given an integer array
	 * @return: Maximum profit
	 */
	long maxProfit(vector<int> &prices) {
		auto const N = prices.size();
		if (N == 0)
			return 0;
		vector<vector<vector<long>>> dp(
				N + 2, vector<vector<long>>(
						3, vector<long>(
								2, std::numeric_limits<int>::min())));
		dp[0][0][0] = 0;
		for (int i = 0; i < N + 1; i++) {
			for (int j = 0; j < 2; j++) {
				dp[i + 1][j][0] = max(dp[i + 1][j][0], dp[i][j][0]);
				dp[i + 1][j][1] = max( { dp[i + 1][j][1], dp[i][j][1], dp[i][j][0] - prices[i] });
				dp[i + 1][j + 1][0] = max( { dp[i + 1][j + 1][0], dp[i][j+1][0], dp[i][j][1] + prices[i] });
			}
		}
//		for (int i = 0; i < N + 1; i++) {
//			for (int j = 0; j < 2 + 1; j++) {
//				printf("(%ld, %ld) | ", dp[i][j][0], dp[i][j][1]);
//			}
//			cout << endl;
//		}
		long ans = 0;
		for (int j = 0; j < 3; j++) {
			ans = max(ans, dp[N][j][0]);
		}
		return ans;
	}
};

int main() {
	Solution sol;
	vector<vector<int>> prices_vec = { { 1, -2, 3, -1, -4, 2, 3, 7 }, { 1, 3, 4, 1 }, { 2, 1, 4, 5, 2, 9, 7 } };
	for (auto& prices : prices_vec) {
		auto ans = sol.maxProfit(prices);
		cout << "ans: " << ans << endl;
	}

	return 1;
}
