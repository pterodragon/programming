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

#define testcase_neq(res, exp)                  \
  {                                         \
    cout << #res << " = " << res << '\t';   \
    bool ok = ((res) != (exp));             \
    cout << " -- " << (ok ? "OK" : "FAIL"); \
    if (!ok) cout << "; exp != " << exp;     \
    cout << '\n';                           \
    cout.flush();                           \
    assert(ok);                             \
  }
using namespace std;

struct Test {
  Test(string_view sv_) : T(sv_), n(T.size()), sa(sv_) {
    cout << "T: " << T << '\n';
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
        cout << "sv: " << sv << '\n';
        auto v = sa.binary_search(sv);
        for (auto e: v) {
          cout << "e: " << e << '\t';
          string_view res(T.data() + e, sv.size()); 
          testcase(res, sv);
        }
      }
    }
  }

  static void test_lcs() {
    for (auto [s1, s2, exp] : {array<string_view, 3>{"gatagaca", "cata", "ata"},
                               {"jdfkal", "vq", ""},
                               {"aaa", "aaa", "aaa"},
                               {"c", "aabbbdeeefffff", ""},
                               {"ba", "xxxa", "a"},
                               {"babaabaaabaaaabaaaa", "aaabba", "aaab"},
                               {"babaabaaabaaaabaaaaa", "aaaaa", "aaaaa"},
                               {"babaabaaabaaaabaaaaa", "", ""},
                               {"", "", ""},
                               {"xxxa", "ba", "a"}}) {
      auto actual = SuffixArray<>::lcs(s1, s2);
      testcase(actual, exp)
      actual = SuffixArray<>::lcs(s2, s1);
      testcase(actual, exp)
      actual = SuffixArray<>::lcs<'|'>(s2, s1);
      testcase(actual, exp)
      actual = SuffixArray<>::lcs<'|'>(s1, s2);
      testcase(actual, exp)
      actual = SuffixArray<27, 'a'>::lcs<'{'>(s2, s1);
      testcase(actual, exp)
      actual = SuffixArray<27, 'a'>::lcs<'{'>(s1, s2);
      testcase(actual, exp)
      actual = SuffixArray<256>::lcs<'\xff'>(s2, s1);
      testcase(actual, exp)
      actual = SuffixArray<256>::lcs<'\xff'>(s1, s2);
      testcase(actual, exp)
    }
  }

 private:
  string T;
  int n;
  SuffixArray<> sa;
};

void run_test() {
  Test test("babaabaaabaaaabaaaaa");
  test.test_lcp(
    {0, 1, 2, 3, 4, 4, 3, 8, 2, 7, 6, 1, 6, 5, 4, 0, 5, 4, 3, 2});
  test.test_lrs("aaabaaaa");

  Test::test_lcs();
}

int main(int argc, char** argv) {
  if (argc > 1) {
    auto sv = string_view(argv[1]);
    auto sv2 = argv[2] ? string_view(argv[2]) : string_view{};
    cout << "n: " << sv.length() << '\n';
    SuffixArray sa(sv);
    sa.print();
    auto [l, r] = sa.lrs();
    cout << "lrs of " << sv << " is " << sv.substr(l, r) << '\n';
    cout << "lcp of " << sv << " is " << sa.lcp() << '\n';
    if (!sv2.empty()) {
      auto lcs = SuffixArray<>::lcs(sv, sv2);
      cout << "lcs of (" << sv << ", " << sv2 << ") is " << lcs << '\n';
    }
  } else {
    run_test();
  }
}
