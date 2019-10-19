#include "solution.hpp"
#include <iostream>

using namespace std;
int main() {
  Solution sol;
  vector<int> c{2, 3, 5, 6};
  int res = sol.change(10, c);
  cout << "res: " << res << '\n';
}
