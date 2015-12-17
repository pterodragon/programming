#include <bits/stdc++.h>
using namespace std;

template<typename T>
vector<T> read_vector(int n, char const* cstr) {
	vector<T> A;
	A.reserve(n);
	for (int i = 0; i < n; i++) {
		int z;
		scanf(cstr, &z);
		A.push_back(z);
	}
	return A;
}

int main() {
	int N;
	scanf("%d", &N);

	vector<int> A = read_vector<int>(N, "%d");
	vector<string> adj_matrix;
	adj_matrix.reserve(N);
	for (int i = 0; i < N; i++) {
		string s;
		cin >> s;
		adj_matrix.push_back(s);
	}

//	for (int i = 0; i < N; i++) {
//		cout << adj_matrix[i] << " ";
//	}

	return 0;
}
