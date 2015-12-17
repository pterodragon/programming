#include <bits/stdc++.h>
using namespace std;

template<typename T>
vector<T> read_vector(int n) {
	vector<T> A;
	A.reserve(n);
	for (int i = 0; i < n; i++) {
		int z;
		scanf("%d", &z);
		A.push_back(z);
	}
	return A;
}

int main() {
	int N;
	scanf("%d", &N);

	vector<int> A = read_vector<int>(N);
	for (auto& i : A) {
		cout << i << ' ';
	}
	cout << endl;

	vector<int> adj_matrix;
	for (int i = 0; i < N; i++) {
		read_vector<int>(N);
	}

//	for (int i = 0; i < N; i++) {
//		for (int j = 0; j < N; j++) {
//			cout << adj_matrix[i][j] << " ";
//		}
//		cout << endl;
//	}

	return 0;
}
