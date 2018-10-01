#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  vector<vector<int>> m_ans;
  int req = 0;
  void dfs(TreeNode* node, int sum, vector<int>& path) {
    if (!node) return;
    if (!(node->left || node->right)) {
      if (sum + node->val == req) {
        path.push_back(node->val);
        m_ans.push_back(path);
        path.pop_back();
      }
      return;
    }
    path.push_back(node->val);
    dfs(node->left, sum + node->val, path);
    dfs(node->right, sum + node->val, path);
    path.pop_back();
  }
  vector<vector<int>> pathSum(TreeNode* root, int sum) {
    if (!root) {
      return {};
    }
    req = sum;
    vector<int> path;
    dfs(root, 0, path);
    return m_ans;
  }
};
#endif /* SOLUTION_HPP */
