#include "solution.hpp"
#include <prettyprint.hpp>

#include <iostream>
using namespace std;

int main() {
  Solution sol;
  TreeNode *a = nullptr;
  // TreeNode* a = new TreeNode(1);
  // a->left = new TreeNode(2);
  // a->right = new TreeNode(2);
  // a->left->left = new TreeNode(2);
  int x = sol.countNodes(a);
  cout << "ans: " << x << '\n';
  return 0;
}
