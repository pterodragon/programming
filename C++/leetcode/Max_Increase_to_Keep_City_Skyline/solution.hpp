#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxIncreaseKeepingSkyline(vector<vector<int>>& g) {
    const int N = g.size();
    vector<int> a(N);  // top view max
    vector<int> b(N);  // left view max
    for (int q = 0; q < N; ++q) b[q] = *max_element(cbegin(g[q]), cend(g[q]));
    for (int w = 0; w < N; ++w) {
      int e = 0;
      for (int q = 0; q < N; ++q) e = max(e, g[q][w]);
      a[w] = e;
    }
    int res = 0;
    for (int q = 0; q < N; ++q)
      for (int w = 0; w < N; ++w) res += max(0, min(a[w], b[q]) - g[q][w]);

    return res;
  }
};
#endif /* SOLUTION_HPP */
