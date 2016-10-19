#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
        /**
         * @param costs n x 3 cost matrix
         * @return an integer, the minimum cost to paint all houses
         */
        int minCost(vector<vector<int>>& costs) {
            const int n = costs.size();
            if (n == 0) return 0;
            const long int_max = numeric_limits<int>::max();

            vector<vector<long>> dp(n, vector<long>(3, int_max)); // dp(n, c) min cost painting houses of no. 0..n and final color is c
            for (int j = 0; j < 3; ++j) {
                dp[0][j] = costs[0][j];
            }
            for (int i = 1; i < n; ++i) {
                for (int j = 0; j < 3; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        dp[i][j] = min(dp[i][j], j == k ? int_max : dp[i - 1][k] + costs[i][j]);
                    }
                }
            }
            for (const auto& v: dp) {
                for (auto e : v) {
                    printf("%ld, ", e);
                }
                puts("");
            }
            return *min_element(begin(dp[n - 1]), end(dp[n - 1]));
        }
};

int main() {
    vector<vector<int>> test = {{14, 2, 11}, {11, 14, 5}, {14, 3, 10}};
    cout << Solution().minCost(test);
    return 0;
}
