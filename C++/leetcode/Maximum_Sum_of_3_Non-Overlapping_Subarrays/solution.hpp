#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
    auto arrsum = [&nums](int a, int b) {
      int s = 0;
      for (int i = a; i < b; ++i) {
        s += nums[i];
      }
      return s;
    };
    const int N = nums.size();
    const int inf = 0x3f3f3f3f;
    vector<int> dp_(3 * N, -inf);
    auto dp = (int(*)[N])(&dp_[0]);
    vector<int> idx_(3 * N * 3, 0);
    auto idx = (int(*)[N][3])(&idx_[0]);
    int ans[3] = {inf, inf, inf};
    for (int t = 0; t < 3; ++t) {
      int x = t % 2;
      int start = (t + 1) * k - 1;
      ans[t] = start;
      for (int a = start; a < N;
           ++a) {  // index where the new subarray may end
        dp[t][a] = a > start ? dp[t][a - 1] : -inf; // init as the prev sum
        if (a > start) {
          copy(begin(idx[t][a - 1]), end(idx[t][a - 1]), begin(idx[t][a]));
        }
        // max sum when array is placed
        int es = -inf;
        if (t == 0) {
          es = arrsum(a - k + 1, a + 1);
        } else {
          int prev = dp[t - 1][a - k];
          if (prev != -inf) {
            es = arrsum(a - k + 1, a + 1) + prev;
          }
        }
        // ---
        if (es > dp[t][a]) {
          //cout << "(t, a) = " << '(' << t << ", " << a << ')' << '\n';
          //cout << "(es, dp[t][a]) = " << '(' << es << ", " << dp[t][a] << ')' << '\n';
          if (t > 0) {
            copy(begin(idx[t - 1][a - k]), end(idx[t - 1][a - k]), begin(idx[t][a]));
          }
          idx[t][a][t] = a - k + 1;
          copy(begin(idx[t][a]), end(idx[t][a]), begin(ans));
          dp[t][a] = es;
        }
      }
      //cout << "idx:\n";
      for (int t = 0; t < 3; ++t) {
        for (int a = 0; a < N; ++a) {
          for (int i = 0; i < 3; ++i) {
            //cout << idx[t][a][i] << ",";
          }
          //cout << "| ";
        }
        //cout << '\n';
      }
      //cout << '\n';
      //cout << "ans:\n";
      for (int a = 0; a < 3; ++a) {
        //cout << ans[a] << ", ";
      }
      //cout << '\n';
    }
    //cout << "dp:\n";
    for (int t = 0; t < 3; ++t) {
      for (int a = 0; a < N; ++a) {
        //cout << dp[t][a] << ", ";
      }
      //cout << '\n';
    }
    //cout << '\n';
    return {ans[0], ans[1], ans[2]};
  }
};

#endif /* SOLUTION_HPP */
