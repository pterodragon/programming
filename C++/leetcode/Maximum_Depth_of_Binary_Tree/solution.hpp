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
    int maxDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        } else {
            return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
        }
    }
};

#endif /* SOLUTION_HPP */
