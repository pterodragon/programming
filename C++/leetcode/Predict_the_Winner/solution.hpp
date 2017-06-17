#ifndef SOLUTION_HPP
#define SOLUTION_HPP 

#include <vector>

using namespace std;

class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        if (nums.empty()) return true;
        const size_t L = nums.size();
        vector<vector<int>> dp(L, vector<int>(L));
        for (size_t i = 0; i < L; ++i) {
            dp[i][i] = nums[i];
        }
        for (size_t r = 1; r < L; ++r) { // r = subarray length - 1
            for (size_t i = 0; i + r < L; ++i) {
                dp[i][i+r] = max(nums[i] - dp[i + 1][i+r], nums[i+r] - dp[i][i+r - 1]);
            }
        }
        return dp[0][L - 1] >= 0;
    }
};

#endif /* SOLUTION_HPP */
