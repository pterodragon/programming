#ifndef SOLUTION_HPP
#define SOLUTION_HPP 

#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

using namespace std;

class NumArray {
public:
    vector<int> psum;
    NumArray(vector<int> nums) {
        partial_sum(begin(nums), end(nums), back_inserter(psum));
    }
    
    int sumRange(int i, int j) {
        return psum[j] - (i > 0 ? psum[i - 1] : 0);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * int param_1 = obj.sumRange(i,j);
 */
#endif /* SOLUTION_HPP */
