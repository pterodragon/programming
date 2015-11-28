#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	/**
	 * @param nums: A list of integers
	 * @param k: An integer denote to find k non-overlapping subarrays
	 * @return: An integer denote the sum of max k non-overlapping subarrays
	 */
	int maxSubArray(vector<int> nums, int k) {
		int ninf = std::numeric_limits<int>::min();
		auto L = nums.size();
		vector<vector<vector<int>>> v;
		v.reserve(L);
		for (int i = 0; i < L; i++) {
			v.emplace_back(vector<vector<int>>(k + 1, { ninf, ninf, ninf }));
		}

		v[0][0][0] = 0;
		for (int i = 0; i < L - 1; i++) {
			for (int j = 0; j < k; j++) {
				v[i + 1][j][0] = max( { v[i + 1][j][0], v[i][j][0], v[i][j][2] } );
				v[i + 1][j][1] = max( { v[i + 1][j][1], v[i][j][1] + nums[i], v[i][j][0] + nums[i] });
				v[i + 1][j + 1][2] = max(v[i + 1][j + 1][2], v[i + 1][j][1] + nums[i]);
			}
		}

		for (int i = 0; i < L; i++) {
			for (int j = 0; j < k + 1; j++) {
				printf("(%d, %d, %d) ", v[i][j][0], v[i][j][1], v[i][j][2]);
			}
			cout << endl;
		}
		cout << endl;

		return max(v[L - 1][k][0], v[L - 1][k][2]);
	}
};

int main(int argc, char const *argv[]) {
	Solution sol;
	vector<int> nums = { 1, 2, 3, 4, -5, -5, 1, -4, 2, -5, 7 };

	auto ans = sol.maxSubArray(nums, 2);
	printf("ans = %d\n", ans);
}
