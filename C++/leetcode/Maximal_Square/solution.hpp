#ifndef SOLUTION_HPP
#define SOLUTION_HPP 

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        const size_t H = matrix.size();
        const size_t W = matrix[0].size();
        vector<vector<int>> dp(H, vector<int>(W));
        int max_side = 0;
        for (size_t r = 0; r < H; ++r) {
            for (size_t s = 0; s < W; ++s) {
                if (r == 0 || s == 0) {
                    dp[r][s] = matrix[r][s] == '1';
                } else {
                    dp[r][s] = matrix[r][s] == '1' ? 1 + min({dp[r - 1][s - 1], dp[r][s - 1], dp[r - 1][s]}) : 0;
                }
                max_side = max(max_side, dp[r][s]);
            }
        }
        return max_side * max_side;
    }
};

#endif /* SOLUTION_HPP */
