#ifndef SOLUTION_HPP
#define SOLUTION_HPP 

#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMinStep(string board, string hand) {
        // aim for a short dfs solution using recursion!
        std::sort(hand.begin(), hand.end());
        do {
        } while(std::next_permutation(hand.begin(), hand.end()));
        return 0;
    }
};

#endif /* SOLUTION_HPP */
