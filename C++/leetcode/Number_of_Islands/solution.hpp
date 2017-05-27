#ifndef SOLUTION_HPP
#define SOLUTION_HPP 

#include <vector>
#include <array>
#include <deque>

using namespace std;

class Solution {
public:
    int size_x;
    int size_y;
    vector<vector<char>>* grid;

    int numIslands(vector<vector<char>>& grid) {
        if (grid.size() == 0 || grid[0].size() == 0) return 0;
        this->grid = &grid;
        size_x = grid.size();
        size_y = grid[0].size();
        int result = 0;
        for (int i = 0; i < size_x; ++i) {
            for (int j = 0; j < size_y; ++j) {
                if (is_new_land(i, j)) {
                    ++result;
                    flood(i, j);
                }
            }
        }
        return result;
    }

    bool is_new_land(int i, int j) {
        return (*grid)[i][j] != 1 && (*grid)[i][j] == '1';
    }

	void flood(int x, int y) {
        (*grid)[x][y] = 1;
        if (x + 1 < size_x && is_new_land(x + 1, y)) flood(x + 1, y);
        if (y + 1 < size_y && is_new_land(x, y + 1)) flood(x, y + 1);
        if (x - 1 >= 0 && is_new_land(x - 1, y)) flood(x - 1, y);
        if (y - 1 >= 0 && is_new_land(x, y - 1)) flood(x, y - 1);
	}
};

#endif /* SOLUTION_HPP */
