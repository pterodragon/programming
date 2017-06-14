#ifndef SOLUTION_HPP
#define SOLUTION_HPP 

#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

class Solution {
public:
    int findRotateSteps(string ring, string key) {
        const int rl = ring.size();
        auto dist = [rl](int p, int q){ int a = abs(q - p); return min(a, rl - a); };
        vector<vector<int>> h(26, vector<int>()); //{char - 'a': [list of positions of char]} for the ring
        for (size_t i = 0; i < ring.size(); ++i) {
            h[ring[i] - 'a'].push_back(i);
        }
        struct ps {
            int pos;
            int step;
        };
        vector<ps> q = {{0, 0}};
        for (auto kc : key) {
            vector<ps> r;
            for (int i: h[kc - 'a']) {
                int pos_new = -1;
                int step_new = 1 << 30; // for each round, at most 50 + 1 steps (turn half ring and press button)
                for (ps e: q) {
                    int step_proposed = e.step + dist(i, e.pos) + 1;
                    if (step_proposed < step_new) {
                        pos_new = i; 
                        step_new = step_proposed;
                    }
                }
                r.push_back({pos_new, step_new});
            }
            swap(q, r);
        }
        int min = 1 << 30;
        for (ps e: q) {
            if (e.step < min) {
                min = e.step;
            }
        }

        return min;
    }
};

#endif /* SOLUTION_HPP */
