#include <exception>
#include <fstream>
#include <string>
#include <utility>

#include "read_test_case.hpp"

using namespace std;

struct ParseError : std::exception {};

Input::PrereqPair readPair(ifstream &file) {
    int x, y;
    if (file.get() == '[' && file >> x && file.get() == ',' &&
        file >> y && file.get() == ']') {
        return {x, y};
    }
    throw ParseError();
}

Input read_input(const char *filepath) {
    ifstream file(filepath);
    Input input;
    if (!(file >> input.nCourses && file.get() == ',')) throw ParseError();
    if ((file >> ws).get() != '[') throw ParseError();
    if (file.peek() == ']') return input;
    char c;
    do {
        input.prereqPairs.emplace_back(readPair(file));
    } while ((c = file.get()) == ',');
    if (c != ']') throw ParseError();

    return input;
}

std::vector<int> read_output(const char *filepath) {
    ifstream file(filepath);
    if (file.get() != '[') throw ParseError();
    std::vector<int> output;
    char c;
    int x;
    do {
        if (file >> x) {
            output.push_back(x);
        } else {
            throw ParseError();
        }
    } while ((c = file.get()) == ',');
    if (c != ']') throw ParseError();
    return output;
}
