#include <bitset>
#include <cassert>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_set>

#include "suffix_array.hpp"

using namespace std;

int main() {
  string T = "babaabaaabaaaabaaaaa$";
  int n = T.size();
  cout << "n: " << n << '\n';
  SuffixArray sa(T);
  sa.print();
  unordered_set<string_view> s;
  for (int q = 0; q < T.size(); ++q) {
    for (int w = 1; q + w < T.size(); ++w) {
      string_view sv(T.data() + q, w);
      if (s.find(sv) != end(s)) continue;
      s.insert(sv);
      int pos = sa.binary_search(sv);
      cout << "sv: " << sv << "; pos: " << pos << ", q: " << q << ", w: " << w
           << '\t';
      cout.flush();
      assert(string(T, pos, w) == string(T, q, w));
      cout << " -- OK\n";
      string s_fail = string(sv) + "x";
      pos = sa.binary_search(s_fail);
      cout << "s_fail: " << s_fail << "; pos: " << pos << '\t';
      cout.flush();
      assert(pos == -1);
      cout << " -- OK\n";
    }
  }
  auto lcp = sa.lcp();
  vector exp_lcp{0, 0, 1, 2, 3, 4, 4, 3, 8, 2, 7, 6, 1, 6, 5, 4, 0, 5, 4, 3, 2};
  assert(!empty(lcp));
  cout << "lcp = ";
  for (auto e : lcp) cout << e << ' ';
  cout.flush();
  assert(lcp == exp_lcp);
  cout << " -- OK\n";
  auto [z, x] = sa.lrs();
  string_view sv_lrs(T.data() + z, x);
  cout << "sv_lrs: " << sv_lrs << '\t';
  cout.flush();
  assert(sv_lrs == "aaabaaaa");
  cout << " -- OK\n";
}
