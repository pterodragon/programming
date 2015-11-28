#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <array>

using namespace std;

class Solution {
public:
	/**
	 * @param nums: A list of integers
	 * @param k: An integer denote to find k non-overlapping subarrays
	 * @return: An integer denote the sum of max k non-overlapping subarrays
	 */
	int maxSubArray(vector<int> nums, int k) {
		constexpr const int NINF = numeric_limits<int>::min();
		auto L = nums.size();
		vector<vector<vector<long>>> v( //
				L + 1, vector<vector<long>>(//
						k + 2,//
						{	NINF, NINF}));
		vector<long> ps;
		ps.reserve(L);
		copy(begin(nums), end(nums), back_inserter(ps));
		partial_sum(begin(ps), end(ps), begin(ps));
		cout << "Partial sum:" << endl;
		for (auto i : ps)
			cout << i << " ";
		cout << endl;

		v[0][0][0] = 0; // until the 0th (no number), transacted 0 times, currently not picking the number at 0th (no number)
		v[0][0][1] = 0; // until the 0th (no number), transacted 0 times, currently picking the number at 0th (no number)
		for (int i = 0; i < L; i++)
			for (int j = 0; j < k + 1; j++)
				v[i + 1][j][0] = max(v[i + 1][j][0], v[i][j][0]), //
				v[i + 1][j][1] = max( { v[i + 1][j][1], v[i][j][1], v[i][j][0] - ps[i] }), //
				v[i + 1][j + 1][0] = max( { v[i + 1][j + 1][0], v[i][j][1] + ps[i], v[i][j][0] + nums[i] } );

		auto p = [](long i) {
			return (i <= NINF) ? string("-∞") : to_string(i);
		};

		for (int i = 0; i < L + 1; i++) {
			for (int j = 0; j < k + 1; j++) {
				cout << setw(3) << p(v[i][j][0]) << ", " << setw(3) << p(v[i][j][1]) << " | ";
			}
			cout << endl;
		}
		cout << endl;

		return v[L][k][0];
	}
};

int main(int argc, char const *argv[]) {
	constexpr const int NINF = numeric_limits<int>::min();
	Solution sol;
	using P = pair<vector<int>, int>;
	vector<P> numvecs { //
	P( { 1, 2, 3, 4, -5, -5, 1, -4, 2, -5, 7 }, 2), //
	P( { 1 }, 1), //
	P( { -1 }, 1), //
	P( { -1, 2 }, 1), //
	P( { 2, -1 }, 1), //
	P( { -1, 2, -1 }, 3), //
	P( { 1, 2, 3 }, 2), //
	P( { -1, -2, -3, -100, -1, -50}, 2), //
	P( {NINF, 1, NINF, -1, NINF, 3, NINF, -1}, 5), // something wrong here
	P( { 2, 3, 4 }, 1) };
	const vector<int> ans_check { 17, 1, -1, 2, 2, 0, 6, -2, NINF + 2, 9 };
	vector<int> answers;

	for (auto& P : numvecs) {
		cout << "k = " << P.second << ", orig vec:" << endl;
		for (auto i : P.first)
			cout << i << " ";
		cout << endl;
		auto ans = sol.maxSubArray(P.first, P.second);
		answers.push_back(ans);
		printf("ans = %d\n", ans);
		cout << string(50, '-') << endl;
	}
	for (int i = 0; i < ans_check.size(); i++) {
		auto left = ans_check[i];
		auto right = answers[i];
		cout << boolalpha << (left == right) << ", " << left << ", " << right << endl;
	}

}

