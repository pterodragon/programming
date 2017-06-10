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
    int findBottomLeftValue(TreeNode* root) {
        int h = 0;
        return helper(root, h);
    }
    int helper(TreeNode* root, int& height) {
        if (root == nullptr) {
            height = -1;
            return -1;
        }
        int lh = height + 1;
        int lval = helper(root->left, lh);
        int rh = height + 1;
        int rval = helper(root->right, rh);
        if (lh == -1 && rh == -1) { // no children
            return root->val;
        } else if (lh >= rh) {
            height = lh;
            return lval;
        } else {
            height = rh;
            return rval;
        }
    }
};

#endif /* SOLUTION_HPP */
