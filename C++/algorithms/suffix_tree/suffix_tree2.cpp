#include <iomanip>
#include <iostream>

#include "suffix_tree2.hpp"

void SuffixTree2::print() const {
  cout << "f: ";
  for (unsigned i = 0; i < q; ++i) {
    if (rps[i].len < INF / 2) printf("f[%d] = %d | ", i, f[i]);
  }
  cout << '\n';
  cout << "g: ";
  for (unsigned i = 0; i < q; ++i) {
    for (auto [k, v] : g[i]) {
      printf("g(%d, [%c](%d, %d)) = %d | ", i, k, rps[v].lp,
             (rps[v].len > INF / 2) ? N - 1 : (rps[v].lp + rps[v].len - 1), v);
    }
  }
  cout << '\n';
}

