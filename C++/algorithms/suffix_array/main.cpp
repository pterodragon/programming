#include <bitset>
#include <cassert>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_set>

#include "prettyprint.hpp"
#include "suffix_array.hpp"

#define testcase(res, exp)                  \
  {                                         \
    cout << #res << " = " << res << '\t';   \
    bool ok = ((res) == (exp));             \
    cout << " -- " << (ok ? "OK" : "FAIL"); \
    if (!ok) cout << "; exp = " << exp;     \
    cout << '\n';                           \
    cout.flush();                           \
    assert(ok);                             \
  }

using namespace std;

struct Test {
  Test(string_view sv_) : T(sv_), n(T.size()), sa(sv_) {
    cout << "n: " << n << '\n';
    sa.print();

    test_binary_search();
  }

  void test_lrs(string exp_lrs) {
    auto [z, x] = sa.lrs();
    string_view sv_lrs(T.data() + z, x);
    testcase(sv_lrs, exp_lrs);
  }

  void test_lcp(vector<int> exp_lcp) {
    auto lcp = sa.lcp();
    testcase(lcp, exp_lcp);
  }

  void test_binary_search() {
    unordered_set<string_view> s;
    for (int q = 0; q < T.size(); ++q) {
      for (int w = 1; q + w < T.size(); ++w) {
        string_view sv(T.data() + q, w);
        if (s.find(sv) != end(s)) continue;
        s.insert(sv);
        int pos = sa.binary_search(sv);
        cout << "pos: " << pos << ", q: " << q << ", w: " << w << '\t';
        testcase(string(T, pos, w), string(T, q, w));
        string s_fail = string(sv) + "#";
        pos = sa.binary_search(s_fail);
        cout << "s_fail: " << s_fail << '\t';
        testcase(pos, -1);
      }
    }
  }

  static void test_lcs() {
    for (auto [s1, s2, exp] : {array<string, 3>{"gatagaca", "cata", "ata"},
                               {"jdfkal", "vq", ""},
                               {"aaa", "aaa", "aaa"},
                               {"c", "aabbbdeeefffff", ""},
                               {"ba", "xxxa", "a"},
                               {"xxxa", "ba", "a"}}) {
      auto [a, b] = SuffixArray::lcs(s1, s2);
      string_view res(s1.data() + a, b);
      testcase(res, exp)
    }
  }

 private:
  string T;
  int n;
  SuffixArray sa;
};

int main() {
  Test test("babaabaaabaaaabaaaaa$");
  test.test_lcp(
      {0, 0, 1, 2, 3, 4, 4, 3, 8, 2, 7, 6, 1, 6, 5, 4, 0, 5, 4, 3, 2});
  test.test_lrs("aaabaaaa");

  Test::test_lcs();
}
