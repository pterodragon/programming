#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
  int msb(int x) { // most significant bit, assert x >= 0
    unsigned y = x;
    y |= y >> 1;
    y |= y >> 2;
    y |= y >> 4;
    y |= y >> 8;
    y |= y >> 16;
    ++y;
    return y >> 1;
  }
  int height(TreeNode *root) {
    int ans = -1;
    do {
      root = root->left;
      ++ans;
    } while (root);
    return ans;
  }

  bool num_is_node(TreeNode *root, int x) {
    unsigned m = msb(x);
    while (m >>= 1) {
      if (!root)
        return false;
      if (m & x) {
        root = root->right;
      } else {
        root = root->left;
      }
    }
    return root != nullptr;
  }

  int countNodes(TreeNode *root) {
    if (!root)
      return 0;
    int h = height(root);
    int l = 1 << h;                 // min node count
    int r = ((unsigned)l << 1) - 1; // max node count
    if (num_is_node(root, r))
      return r;
    while (l < r) {
      int m = (l + r + 1) / 2;
      if (num_is_node(root, m)) {
        l = m;
      } else {
        r = m - 1;
      }
    }
    return l;
  }
};
#endif /* SOLUTION_HPP */
