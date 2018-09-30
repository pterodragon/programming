#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "read_test_case.hpp"

ostream &operator<<(ostream &os, TreeNode *node) {
  if (node == nullptr) {
    return os << '*';
  } else {
    return os << '{' << node->val << ", " << node->left << ", " << node->right
              << '}';
  }
}

TreeNode *read_tree(ifstream &file) {
  // FIXME: delete the whole tree after testing
  char c = file.get();
  if (c == '*')
    return nullptr;
  if (c != '{')
    throw ParseError("expected '{' for a new tree");
  int val;
  if (!(file >> val))
    throw ParseError("can't read int after '{'");
  if (file.get() != ',')
    throw ParseError("expected ',' after int in a tree");
  TreeNode *left = read_tree(file);
  if (file.get() != ',')
    throw ParseError("expected ',' after first tree");
  TreeNode *right = read_tree(file);
  if (file.get() != '}')
    throw ParseError("expected '}' for the end of a tree");
  TreeNode *node = new TreeNode(val);
  node->left = left;
  node->right = right;
  return node;
}

pair<TreeNode *, TreeNode *> read_input(const char *filepath) {
  ifstream file(filepath);
  TreeNode *p = read_tree(file);
  if (file.get() != '\n')
    throw ParseError("no new line after first tree");
  TreeNode *q = read_tree(file);
  return {p, q};
}

int read_output(const char *filepath) {
  ifstream file(filepath);
  int result;
  file >> result;
  return result;
}
