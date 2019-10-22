#include "solution.hpp"
#include <iostream>

using namespace std;

int main() {
  int n, c;
  cin >> n >> c;
  int a[n - 1];
  int b[n - 1];
  int out[n];

  for (int q = 0; q < n - 1; ++q)
    cin >> a[q];
  for (int q = 0; q < n - 1; ++q)
    cin >> b[q];

  solve(n, c, a, b, out);
  for (int q = 0; q < n; ++q)
    cout << out[q] << ' ';
  cout << '\n';
}
