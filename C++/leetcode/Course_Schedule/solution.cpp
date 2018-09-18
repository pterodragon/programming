#include <algorithm>
#include <cassert>
#include <deque>
#include <iterator>
#include <vector>

using namespace std;

class Solution {
public:
  bool canFinish(int N, vector<pair<int, int>> &prerequisites) {
    if (prerequisites.empty())
      return true;
    struct deg_prop {
      int in_degree = 0;
      int out_degree = 0;
    };
    vector<vector<int>> adj_list(N, vector<int>());
    vector<deg_prop> deg(N);
    for (auto p : prerequisites) {
      adj_list[p.second].push_back(p.first);
      ++deg[p.first].in_degree;
      ++deg[p.second].out_degree;
    }
    deque<int> q;
    for (size_t i = 0; i < deg.size(); ++i) {
      if (deg[i].in_degree == 0) {
        q.push_back(i);
      }
    }
    while (!q.empty()) {
      int node = q.front();
      q.pop_front();
      for (auto neigh : adj_list[node]) {
        --deg[neigh].in_degree;
        if (deg[neigh].in_degree == 0) {
          q.push_back(neigh);
        }
      }
    }
    return all_of(begin(deg), end(deg),
                  [](deg_prop d) { return d.in_degree == 0; });
  }
};

int main() {
  Solution sol;
  vector<pair<int, int>> v1{{0, 1}, {1, 0}};
  vector<pair<int, int>> v2{{1, 0}};
  vector<pair<int, int>> v3{{0, 1}, {1, 2}, {2, 3}, {3, 4}};
  vector<pair<int, int>> v4{{4, 0}, {0, 1}, {1, 2}, {2, 3}, {3, 4}};
  vector<pair<int, int>> v5{{1, 0}, {2, 1}, {3, 2}, {1, 3}};
  assert(!sol.canFinish(2, v1));
  assert(sol.canFinish(2, v2));
  assert(sol.canFinish(5, v3));
  assert(!sol.canFinish(5, v4));
  assert(!sol.canFinish(4, v5));
  return 0;
}
