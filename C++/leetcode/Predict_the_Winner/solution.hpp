#ifndef SOLUTION_HPP
#define SOLUTION_HPP 

#include <vector>

using namespace std;

// class Solution {
// public:
//     bool PredictTheWinner(vector<int>& nums) {
//         if (nums.empty()) return true;
//         const size_t L = nums.size();
//         vector<vector<int>> dp(L, vector<int>(L));
//         for (size_t i = 0; i < L; ++i) {
//             dp[i][i] = nums[i];
//         }
//         for (size_t r = 1; r < L; ++r) { // r = subarray length - 1
//             for (size_t i = 0; i + r < L; ++i) {
//                 dp[i][i+r] = max(nums[i] - dp[i + 1][i+r], nums[i+r] - dp[i][i+r - 1]);
//             }
//         }
//         return dp[0][L - 1] >= 0;
//     }
// };

// reduced space complexity
//    0    1    2    3
// 0  n[0] ...
// 1       n[1] ...
// 2            n[2] ...
// 3                 n[3]
//
// the next iteration (next diagonal depends on the previous diagonal only)
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        if (nums.empty()) return true;
        const size_t L = nums.size();
        vector<int> dp(L); // stores max score margin using nums[x:x + r + 1] where r increases in the loop
        for (size_t i = 0; i < L; ++i) {
            dp[i] = nums[i];
        }
        for (size_t r = 1; r < L; ++r) { // r = subarray length - 1
            for (size_t i = 0; i + r < L; ++i) {
                dp[i] = max(nums[i] - dp[i + 1], nums[i + r] - dp[i]);
            }
        }
        return dp[0] >= 0;
    }
};

#endif /* SOLUTION_HPP */
