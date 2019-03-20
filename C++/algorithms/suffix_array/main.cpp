#include <cassert>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_set>

#include "suffix_array.hpp"

using namespace std;

int main() {
  string T = "babaabaaabaaaab";
  int n = T.size();
  printf("n: %d\n", n);
  T[n] = '$';
  T[++n] = '\0';
  SuffixArray sa(T);
  sa.print();
  unordered_set<string_view> s;
  for (int q = 0; q < T.size(); ++q)
    for (int w = 1; q + w < T.size(); ++w) {
      string_view sv(T.data() + q, w);
      if (s.find(sv) != end(s)) continue;
      s.insert(sv);
      int pos = sa.binary_search(sv);
      cout << "sv: " << sv << "; pos: " << pos << ", q: " << q
           << ", w: " << w << '\t';
      cout.flush();
      assert(string(T, pos, w) == string(T, q, w));
      printf(" -- OK\n");
      string s_fail = string(sv) + "x";
      pos = sa.binary_search(s_fail);
      cout << "s_fail: " << s_fail << "; pos: " << pos << '\t';
      cout.flush();
      assert(pos == -1);
      printf(" -- OK\n");
    }
}
