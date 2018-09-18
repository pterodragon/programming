#include <bits/stdc++.h>
#include <prettyprint.hpp>
using namespace std;

class Solution {
public:
  int maxArea(vector<int> &height) {
    const size_t N = height.size();
    int i = 0;
    int j = N - 1;
    int max_area = 0;
    while (i < j) {
      int dx = j - i;
      int container_height = min(height[j], height[i]);
      max_area = max(max_area, dx * container_height);
      if (height[j] >= height[i]) {
        ++i;
      } else {
        --j;
      }
    }
    return max_area;
  }
};

int main() {
  Solution sol;
  vector<pair<int, vector<int>>> tests = {
      {10, {10, 10, 1, 1, 1, 0}}, {4, {1, 2, 4, 3}}, {3, {0, 1, 1, 1, 1, 0}}};
  for (auto p : tests) {
    cout << "assert " << p.first << " == " << p.second << '\n';
    assert(p.first == sol.maxArea(p.second));
  }
  return 0;
}
