#ifndef SOLUTION_HPP
#define SOLUTION_HPP 

#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;

class Solution {
public:
    vector<pair<int, int>> pacificAtlantic(const vector<vector<int>>& matrix) {
        vector<pair<int, int>> res;
        if (matrix.empty()) {
            return res;
        }
        vector<vector<bitset<2>>> pa(matrix.size(), vector<bitset<2>>(matrix[0].size(), 0)); // first and second bit represents "can go to Pacific/Atlantic ocean" resp.
        for (size_t i = 0; i < matrix.size(); ++i) {
            flood(i, 0, matrix, pa, 0); // down 0th column
            flood(i, matrix[0].size() - 1, matrix, pa, 1); // down N-1th column
        }
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            flood(0, j, matrix, pa, 0); // across 0th row
            flood(matrix.size() - 1, j, matrix, pa, 1); // across N-1th row
        }
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[0].size(); ++j) {
                if (pa[i][j][0] & pa[i][j][1]) {
                    res.push_back({i, j});
                }
            }
        }
        return res;
    }
    void flood(size_t i, size_t j, const vector<vector<int>>& matrix, vector<vector<bitset<2>>>& pa, unsigned ocean_bit) {
        if (pa[i][j][ocean_bit]) return; // visited
        pa[i][j][ocean_bit] = 1;
        if (i > 0 && matrix[i - 1][j] >= matrix[i][j]) {
            flood(i - 1, j, matrix, pa, ocean_bit);
        }
        if (j > 0 && matrix[i][j - 1] >= matrix[i][j]) {
            flood(i, j - 1, matrix, pa, ocean_bit);
        }
        if (i + 1 < matrix.size() && matrix[i + 1][j] >= matrix[i][j]) {
            flood(i + 1, j, matrix, pa, ocean_bit);
        }
        if (j + 1 < matrix[0].size() && matrix[i][j + 1] >= matrix[i][j]) {
            flood(i, j + 1, matrix, pa, ocean_bit);
        }
    }
};

#endif /* SOLUTION_HPP */
