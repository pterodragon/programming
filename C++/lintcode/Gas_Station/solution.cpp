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
		auto sum = accumulate(gas.begin(), gas.end(), 0) - accumulate(cost.begin(), cost.end(), 0);
		if (sum < 0)
			return -1;
		int a = 0;
		for (int i = 0; i < L; i++) {
			if (gas[i] - cost[i] >= 0) {
				a = i;
				break;
			}
		}
		int b = a;
		auto diff = [&gas, &cost](int x) {return gas[x] - cost[x];};
		int gas_remain = diff(a);
		while ((b + 1) % L != a) {
			if (diff((b + 1) % L) + gas_remain >= 0) {
				b = (b + 1) % L;
				gas_remain += diff(b);
			} else if (diff((L + a - 1) % L) + gas_remain >= 0) {
				a = (L + a - 1) % L;
				gas_remain += diff(a);
			} else {
				return -1;
			}
		}
		return a;
	}
};

int main() {
	Solution s;

	vector<vector<int>> gas { { 1, 1, 3, 1 } };
	vector<vector<int>> cost { { 2, 2, 1, 1 } };
	for (int i = 0; i < gas.size(); i++) {
		auto ans = s.canCompleteCircuit(gas[i], cost[i]);
		cout << ans << endl;
		cout << "---" << endl;
	}
	return 1;
}
