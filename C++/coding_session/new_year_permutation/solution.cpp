#include <bits/stdc++.h>
using namespace std;

template<typename T>
vector<T> read_vector(int n, char const* cstr) {
	vector<T> A;
	A.reserve(n);
	for (int i = 0; i < n; i++) {
		T z;
		scanf(cstr, &z);
		A.push_back(z);
	}
	cin.ignore();
	return A;
}

//template<typename T>
//void print_vector(vector<vector<T>> const& vvt) {
//	for (vector<T> vt : vvt) {
//		for (T const& t : vt) {
//			cout << t << " ";
//		}
//		cout << endl;
//	}
//}

template<typename T>
void print_vector(vector<T> v) {
	for (int z = 0; z < v.size(); z++) {
		cout << v[z] << " ";
	}
	cout << endl;
}

void dfs(int i, vector<int> const& A, vector<vector<char> > const& adj_matrix, vector<int>& ans, vector<int>& visited) {
	vector<int> indices;
	stack<int> s;
	s.push(i);
	visited[i] = 1;
	while (!s.empty()) {
		int idx = s.top();
//		printf("popped %d\n", idx);
		s.pop();
		indices.push_back(idx);
//		print_vector(adj_matrix[idx]); cout << "--" << endl;
		for (int z = 0; z < adj_matrix[idx].size(); z++) {
			if (!visited[z] && adj_matrix[idx][z] == '1') {
				s.push(z);
				visited[z] = 1;
			}
		}
	}
//	print_vector(indices);
	sort(indices.begin(), indices.end());
	vector<int> numbers;
	numbers.reserve(indices.size());
	for (int z = 0; z < indices.size(); z++) {
		numbers.push_back(A[indices[z]]);
	}
	sort(numbers.begin(), numbers.end());
	for (int z = 0; z < indices.size(); z++) {
		ans[indices[z]] = numbers[z];
	}
}

void solve(int N, vector<int> const& A, vector<vector<char> > const& adj_matrix) {
	vector<int> visited(N);
	vector<int> ans(N);
	for (int i = 0; i < N; i++) {
		if (!visited[i]) {
			dfs(i, A, adj_matrix, ans, visited);
		}
	}
	for (int i = 0; i < N - 1; i++) {
		cout << ans[i] << " ";
	}
	cout << ans[N - 1] << endl;
}

int main() {
	int N;
	scanf("%d", &N);

	vector<int> A = read_vector<int>(N, "%d");
	vector<vector<char> > adj_matrix;
	adj_matrix.reserve(N);
	for (int i = 0; i < N; i++) {
		adj_matrix.push_back(read_vector<char>(N, "%c"));
	}
	solve(N, A, adj_matrix);

	return 0;
}
