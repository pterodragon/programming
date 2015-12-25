#include <bits/stdc++.h>

using namespace std;

class SegmentTree {
private:
	vector<int> st;
	vector<int> const A;
	int const n;

	int left(int p) {
		return p << 1;
	}

	int right(int p) {
		return (p << 1) + 1;
	}

	void build(int p, int L, int R) { // O(n)
		if (L == R)
			st[p] = A[L];
		else { // recursively compute the values
			build(left(p), L, (L + R) / 2);
			build(right(p), (L + R) / 2 + 1, R);
			st[p]  = st[left(p)] + st[right(p)];
		}
	}

	int elements_in_range(int p, int L, int R, int i, int j) {
		if (i > R || j < L) {
			return 0;
		} else if (L >= i && R <= j) {
//			printf("[%d, %d] (%d, %d), p = %d\n", L, R, i, j, p);
			return st[p];
		} else {
			int p1 = elements_in_range(left(p), L, (L + R) / 2, i, j);
			int p2 = elements_in_range(right(p), (L + R) / 2 + 1, R, i, j);
			return p1 + p2;
		}
	}

public:
	SegmentTree(vector<int> const& A) :
			A(A), n(A.size()) {
		st = vector<int>(4 * n, -1);
		build(1, 0, n - 1);
	}

	int count_of_smaller_number(int a) {
		return elements_in_range(1, 0, n - 1, 0, a - 1);
	}


	void print() const {
		for (auto const& e : st) {
			cout << e << " ";
		}
		cout << endl;
	}
};

vector<int> countOfSmallerNumber(vector<int> &A, vector<int> &queries) {
	vector<int> count(10001);
	for (auto const& a : A) {
		count[a]++;
	}
	SegmentTree st(count);
//	st.print();
	vector<int> ans;
	for (auto const& q: queries) {
		ans.push_back(st.count_of_smaller_number(q));
	}
	return ans;
}

int main() {
	vector<int> A { 1, 2, 7, 8, 5 };
	vector<int> queries { 1, 8, 5 };
	auto ans = countOfSmallerNumber(A, queries);
	for (auto const& a : ans) {
		cout << a << " ";
	}
	cout << endl;

	return 0;
}
