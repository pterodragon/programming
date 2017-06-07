#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "read_test_case.hpp"

std::ostream& operator<<(std::ostream& os, TreeNode* node) {
    if (node == nullptr) {
        os << '*';
    } else {
        os << '{' << node->val << ", " << node->left << ", " << node->right << '}';
    }
    return os;
}

TreeNode* read_tree(const std::string& str, int pos, int endp1) {
    // std::cout << "str.substr = " << str.substr(pos, endp1 - pos + 1) << std::endl;
    // std::cout << "pos = " << pos << ", endp1 = " << endp1 << std::endl;
    if (endp1 - pos == 1 && str[pos] == '*') {
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
    //std::cout << "val = " << val << std::endl;
    auto next_c = [&str](int pos, int endp1, char c) {
        //cout << "going: ";
        int lb = 0;
        while (pos < endp1) {
            cout << str[pos];
            if (str[pos] == c && lb == 0) {
                break;
            } else if (str[pos] == '{') {
                ++lb;
            } else if (str[pos] == '}') {
                --lb;
                if (lb < 0) {
                    throw std::invalid_argument("mismatching braces found");
                }
            }
            ++pos;
        }
        if (pos == endp1) {
            throw std::invalid_argument("expected ',' not found");
        }
        return pos;
    };
    int c2_pos = next_c(c1_pos + 1, endp1, ',');
    //std::cout << "c1_pos = " << c1_pos << ", c2_pos = " << c2_pos << std::endl;
    TreeNode* left = read_tree(str, c1_pos + 1, c2_pos);
    TreeNode* right = read_tree(str, c2_pos + 1, endp1 - 1);
    TreeNode* node = new TreeNode(val);
    node->left = left;
    node->right = right;
    return node;
}

TreeNode* read_input(const char* filepath) {
    ifstream file(filepath);
    std::string line;
    std::getline(file, line);
    int x = line.size();
    return read_tree(line, 0, x);
}

int read_output(const char* filepath) {
    ifstream file(filepath);
    int result;
    file >> result;
    return result;
}

