#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "read_test_case.hpp"

std::ostream &operator<<(std::ostream &os, TreeNode *node) {
  if (node == nullptr) {
    os << '*';
  } else {
    os << '{' << node->val << ", " << node->left << ", " << node->right << '}';
  }
  return os;
}

TreeNode *read_tree(const std::string &str, int pos, int &endp1) {
  // endp1 at most read to this point
  // after the call, end pos = right after the '}' or '*' of the node
  // FIXME: delete the whole tree after testing
  //
  // std::cout << "str.substr = " << str.substr(pos, endp1 - pos + 1) <<
  // std::endl; std::cout << "pos = " << pos << ", endp1 = " << endp1 <<
  // std::endl;
  if (str[pos] == '*') {
    endp1 = pos + 1;
    return nullptr;
  }
  if (str[pos] != '{') {
    throw std::invalid_argument("expected '{' or '*' not found");
  }
  int c1_pos = str.find(',', pos + 1);
  if (c1_pos == std::string::npos) {
    throw std::invalid_argument("expected ',' not found");
  }
  int val = boost::lexical_cast<int>(str.data() + pos + 1, c1_pos - pos - 1);
  if (endp1 - c1_pos < 5) { // {1,*,*} at least ",*,*}" to make a node
    throw std::invalid_argument("invalid syntax after val");
  }
  // std::cout << "val = " << val << std::endl;
  int left_node_end_pos = endp1;
  TreeNode *left = read_tree(str, c1_pos + 1, left_node_end_pos);
  if (str[left_node_end_pos] != ',') {
    throw std::invalid_argument("expected ',' not found");
  }
  if (endp1 - left_node_end_pos < 3) { // {1,*,*} at least ",*}" to make a node
    throw std::invalid_argument("invalid syntax after left child");
  }

  int right_node_end_pos = endp1;
  TreeNode *right = read_tree(str, left_node_end_pos + 1, right_node_end_pos);
  if (str[right_node_end_pos] != '}') { // either *} or }}
    throw std::invalid_argument("expected '}' not found");
  }
  endp1 = right_node_end_pos + 1;
  TreeNode *node = new TreeNode(val);
  node->left = left;
  node->right = right;
  return node;
}

TreeNode *read_input(const char *filepath) {
  ifstream file(filepath);
  std::string line;
  std::getline(file, line);
  std::cout << "-----" << std::endl;
  std::cout << "input: " << std::endl;
  std::cout << line << std::endl;
  std::cout << "-----" << std::endl;
  int x = line.size();
  return read_tree(line, 0, x);
}

int read_output(const char *filepath) {
  ifstream file(filepath);
  int result;
  file >> result;
  return result;
}
