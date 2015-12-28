#include <numeric>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	/**
	 * @param gas: a vector of integers
	 * @param cost: a vector of integers
	 * @return: an integer
	 */
	int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
		auto const L = gas.size();
		int sum = 0;
		int total = 0;
		int j = -1;
		for (int i = 0; i < L; i++) {
			auto diff = gas[i] - cost[i];
			sum += diff;
			total += diff;
			if (sum < 0) {
				j = i;
				sum = 0;
			}
		}
		return total >= 0 ? j + 1 : -1;
	}
};

int main() {
	Solution s;

	vector<vector<int>> gas { { 1, 1, 3, 1 }, { 0, 2, 0, 100 } };
	vector<vector<int>> cost { { 2, 2, 1, 1 }, { 20, 1, 20, 0 } };
	for (int i = 0; i < gas.size(); i++) {
		auto ans = s.canCompleteCircuit(gas[i], cost[i]);
		cout << ans << endl;
		cout << "---" << endl;
	}
	return 1;
}
