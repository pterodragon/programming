#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
        int maxArea(vector<int>& height) {
            const size_t N = height.size();
            int i = 0;
            int j = N - 1;
            int max_area = 0;
            while (i < j) {
                int dx = j - i;
                int container_height = min(height[j], height[i]);
                max_area = max(max_area, dx* container_height);
                if (height[j] >= height[i]) {
                    ++i;
                } else {
                    --j;
                }
            }
            return max_area;
        }
};

