#ifndef SOLUTION_HPP
#define SOLUTION_HPP 

#include <vector>

using namespace std;

class Solution {
public:
    int maxSubArray(const vector<int>& nums) {
        if (nums.empty()) return 1337;
        long local = nums[0];
        long global = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
            local = local < 0 ? nums[i] : local + nums[i];
            global = max(global, local);
        }
        return global;
    }
};

#endif /* SOLUTION_HPP */
