#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "prettyprint.hpp"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;
using tii = tuple<int, int>;
using vi = vector<int>;
using vtii = vector<tii>;

class Solution {
public:
  int maximalPathQuality(vector<int> &values, vector<vector<int>> &edges,
                         int maxTime) {
    // Contraints: 0 <= n = values.length <= 1000; 0 <= values <= 10^8;
    // edges.length <= 2000; 10 <= t, maxTime <= 100 at most 4 edges connected
    // to each node
    //
    // run all possible paths from source (dfs at most 10 edges
    // because of contraints) get maximum path quality on the way
    // -> TC = 4^10 <= 10^7

    // build graph
    auto n = values.size();
    vector<vtii> g(n, vtii{}); // u -> (v, t)
    for (auto const &edge : edges) {
      auto u = edge[0];
      auto v = edge[1];
      auto w = edge[2];
      g[u].push_back({v, w});
      g[v].push_back({u, w});
    }

    // go through all paths including with cycle ones
    int const MAX_DEPTH = 10;
    vi visited(n);
    int acc = 0;
    return dfs(MAX_DEPTH, maxTime, visited, acc, 0, g, values);
  }

  int dfs(int depth, int max_w, vi &visited, int &acc, int u,
               vector<vtii> const &g, vi const &values) {
    int ans = 0;
    if (!visited[u])
      acc += values[u];

    visited[u] = 1;
    if (u == 0)
      ans = acc;

    for (auto [v, w] : g[u]) {
      if (int remain = max_w - w; remain >= 0) {
        auto orig_visited = visited[v];
        if (!orig_visited) {
          acc += values[v];
          visited[v] = 1;
        }
        auto ans2 = dfs(depth - 1, remain, visited, acc, v, g, values);
        ans = max(ans, ans2);
        // backtrack
        if (!orig_visited) {
          acc -= values[v];
          visited[v] = 0;
        }
      }
    }
    return ans;
  };
};

#endif /* SOLUTION_HPP */
