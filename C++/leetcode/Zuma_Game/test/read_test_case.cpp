#include <fstream>

#include "read_test_case.hpp"

std::pair<std::string, std::string> read_input(const char* filepath) {
    std::ifstream file(filepath);
    std::string str;
    std::string board;
    std::string hand;
    std::getline(file, board);
    std::getline(file, hand);
    return {board, hand};
}

int read_output(const char* filepath) {
    std::ifstream file(filepath);
    int result;
    file >> result;
    return result;
}

