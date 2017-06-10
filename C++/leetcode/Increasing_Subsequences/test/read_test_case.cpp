#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "read_test_case.hpp"

std::vector<int> read_vector(std::string& str) {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end()); // erase all spaces
    if (str.empty() || str[0] != '[' || str.back() != ']') {
        throw std::invalid_argument("first char not '[' or last char not ']'");
    }
    if (str.size() == 2) {
        return std::vector<int>();
    }
    str.erase(str.begin()); // remove '['
    str.erase(str.end() - 1); // remove ']'
    std::vector<std::string> strs;
    boost::split(strs, str, boost::is_any_of(","));
    std::vector<int> res;
    for (auto& e : strs) {
        int val = boost::lexical_cast<int>(e);
        res.push_back(val);
    }
    return res;
}

std::vector<vector<int>> read_vector_of_vector(std::string& str) {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end()); // erase all spaces
    if (str.empty() || str[0] != '[' || str.back() != ']') {
        throw std::invalid_argument("first char not '[' or last char not ']'");
    }
    if (str.size() == 2) {
        return std::vector<std::vector<int>>();
    }
    std::vector<std::vector<int>> res;
    int start_pos = 1;
    while (true) {
        int close_pos = str.find(']', start_pos);
        if (close_pos == std::string::npos || close_pos + 1 >= str.size()) { // must leave 1 char for the closing ']'
            throw std::invalid_argument("expected ']' not found");
        }
        auto s = str.substr(start_pos, close_pos - start_pos + 1);
        res.push_back(read_vector(s));
        if (str[close_pos + 1] == ']') { // end of vector of vector
            if (close_pos + 2 != str.size()) {
                throw std::invalid_argument("unexpected ']'");
            }
            break;
        } else if (str[close_pos + 1] != ',' || close_pos + 2 >= str.size()) {
            throw std::invalid_argument("expected ',' not found or ',' not followed by anything");
        } else {
            start_pos = close_pos + 2;
        }
    }
    return res;
}


std::vector<int> read_input(const char* filepath) {
    ifstream file(filepath);
    std::string line;
    std::getline(file, line);
    int end = line.size();
    return read_vector(line);
}

std::vector<std::vector<int>> read_output(const char* filepath) {
    ifstream file(filepath);
    std::string line;
    std::getline(file, line);
    int end = line.size();
    return read_vector_of_vector(line);
}

