#ifndef SOLUTION_HPP
#define SOLUTION_HPP

// from http://codeforces.com/blog/entry/18051?locale=en

#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;
class NumArray {
public:
  vector<int> t;
  size_t N;
  NumArray(vector<int> nums) {
    N = nums.size();
    fill_n(back_inserter(t), N * 2, 0);
    copy(begin(nums), end(nums), begin(t) + N);
    build();
  }

  inline void build() {
    for (int a = N - 1; a > 0; --a) {
      t[a] = t[a << 1] + t[a << 1 | 1];
    }
  }

  void update(int a, int val) {
    for (t[a += N] = val; a > 1; a >>= 1) {
      t[a >> 1] = t[a] + t[a ^ 1];
    }
  }

  int sumRange(int l, int r) { // [l, r]; notice this range is closed at both
                               // end unlike the codeforce reference [l, r)
    int sum = 0;
    for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        sum += t[l++];
      if (r & 1)
        sum += t[--r];
    }
    return sum;
  }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */

#endif /* SOLUTION_HPP */
