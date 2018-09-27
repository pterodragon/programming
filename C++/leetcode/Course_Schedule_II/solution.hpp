#include <deque>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> findOrder(int numCourses, vector<pair<int, int>> &prerequisites) {
    struct deg_prop {
      int in_degree = 0;
      int out_degree = 0;
    };
    vector<vector<int>> adj_list(numCourses, vector<int>());
    vector<deg_prop> deg(numCourses);
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
    vector<int> ans;
    while (!q.empty()) {
      int node = q.front();
      q.pop_front();
      ans.push_back(node);
      for (auto neigh : adj_list[node]) {
        --deg[neigh].in_degree;
        if (deg[neigh].in_degree == 0) {
          q.push_back(neigh);
        }
      }
    }
    return ans.size() == numCourses ? ans : vector<int>();
  }
};
