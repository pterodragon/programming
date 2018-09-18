#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <algorithm>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
  bool isSameTree(TreeNode *p, TreeNode *q) {
    if ((p == nullptr) != (q == nullptr)) {
      return false;
    }
    return p == nullptr || (p->val == q->val && isSameTree(p->left, q->left) &&
                            isSameTree(p->right, q->right));
  }
};

#endif /* SOLUTION_HPP */
