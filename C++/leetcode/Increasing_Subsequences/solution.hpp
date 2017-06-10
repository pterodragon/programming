#ifndef SOLUTION_HPP
#define SOLUTION_HPP 

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    std::vector<std::vector<int>> ans;
    std::vector<int> curr;
    int N;
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        N = nums.size();
        curr.reserve(N);
        helper(nums, 0);
        return ans;
    }
    void helper(const vector<int>& nums, int start_pos) {
        if (curr.size() >= 2) {
            ans.push_back(curr);
        }
        bool repeated[201] = {false}; // assumes the range is [-100, 100]
        for (int i = start_pos; i < N; ++i) {
            if ((curr.empty() || nums[i] >= curr[curr.size() - 1]) && repeated[nums[i] + 100] != true) {
                repeated[nums[i] + 100] = true;
                curr.push_back(nums[i]);
                helper(nums, i + 1);
                curr.pop_back();
                if (i != N - 1 && nums[i] == nums[i + 1]) {
                    ++i;
                }
            }
        }
    }
};

#endif /* SOLUTION_HPP */
