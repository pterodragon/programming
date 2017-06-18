#ifndef SOLUTION_HPP
#define SOLUTION_HPP 

#include <vector>
#include <algorithm>

using namespace std;

// class Solution {
// public:
//     int maximalSquare(vector<vector<char>>& matrix) {
//         if (matrix.empty() || matrix[0].empty()) return 0;
//         const size_t H = matrix.size();
//         const size_t W = matrix[0].size();
//         vector<vector<int>> dp(H, vector<int>(W));
//         vector<int> h(H);
//         int max_side = 0;
//         for (size_t r = 0; r < H; ++r) {
//             for (size_t s = 0; s < W; ++s) {
//                 if (r == 0 || s == 0) {
//                     dp[r][s] = matrix[r][s] == '1';
//                 } else {
//                     dp[r][s] = matrix[r][s] == '1' ? 1 + min({dp[r - 1][s - 1], dp[r][s - 1], dp[r - 1][s]}) : 0;
//                 }
//                 max_side = max(max_side, dp[r][s]);
//             }
//         }
//         return max_side * max_side;
//     }
// };

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        const size_t H = matrix.size();
        const size_t W = matrix[0].size();
        const size_t big_s = max(H, W);
        const size_t small_s = min(H, W);
        vector<int> dp(small_s); // space complexity = O(min(H, W))
        int max_side = 0;
        for (size_t r = 0; r < big_s; ++r) {
            int prev_left = 0;
            int pprev_left = 0;
            for (size_t s = 0; s < small_s; ++s) {
                int t = pprev_left;
                pprev_left = dp[s];
                size_t r_ = r;
                size_t s_ = s;
                if (W > H) swap(r_, s_);
                if (r_ == 0 || s_ == 0) {
                    dp[s] = matrix[r_][s_] == '1';
                } else {
                    dp[s] = matrix[r_][s_] == '1' ? 1 + min({prev_left, t, dp[s]}) : 0;
                }
                prev_left = dp[s];
                max_side = max(max_side, dp[s]);
            }
        }
        return max_side * max_side;
    }
};
#endif /* SOLUTION_HPP */
