#include "suffix_tree.hpp"

#include <cassert>
#include <unordered_set>

#include "prettyprint.hpp"

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

class Test {
 public:
  Test(string_view s) : s(s), N(s.size()), st(s) {
    cout << "--- s: " << s << '\n';
  }

  void test_search_all() const {
    cout << __PRETTY_FUNCTION__ << '\n';
    for (int q = 0; q < N; ++q) {
      for (int w = 1; q + w < N; ++w) {
        string_view pat(s.data() + q, w);
        cout << "pat: " << pat << '\t';
        unordered_set<int> exp;
        for (int e = 0; e + pat.size() <= N; ++e)
          if (pat == s.substr(e, pat.size())) exp.insert(e);

        auto v = st.search_all(pat);
        unordered_set<int> actual(begin(v), end(v));
        testcase(actual, exp);
      }
    }
  }

  void test_lrs() const {
    cout << __PRETTY_FUNCTION__ << '\n';
    // compute lrs by dynamic programming
    vector<vector<int>> dp(N, vector<int>(N));
    // dp[i][j]: longest of suffix of s[i:j+1] which is repeating in s
    pair<int, int> res;  // len, end idx
    for (int q = 1; q < N; ++q) {
      for (int w = q + 1; w < N; ++w) {
        dp[q][w] = s[q - 1] == s[w - 1] ? dp[q - 1][w - 1] + 1 : 0;
        res = max(res, {dp[q][w], w});
      }
    }
    auto [len, res_w] = res;
    auto res_sv = s.substr(res_w - len, len);
    testcase(st.lrs(), res_sv);
    testcase(st.lrs_dfs(), res_sv);
  }

  void test_lcs() const {
    cout << __PRETTY_FUNCTION__ << '\n';
    // check if any substring is the longest common substring with itself
    string uc(1, 'a' + 27);
    for (int q = 0; q < N; ++q) {
      for (int w = q + 1; q + w < N; ++w) {
        string_view pat(s.data() + q, w);
        auto arg = string(pat);
        auto lcs = SuffixTree<29, 'a'>::lcs(s, arg);
        testcase(lcs, pat);
        arg = uc + string(pat);
        lcs = SuffixTree<29, 'a'>::lcs(s, arg);
        testcase(lcs, pat);
      }
    }
    auto lcs = SuffixTree<29, 'a'>::lcs(s, uc);
    testcase(lcs, "");
  }

  void test_substr() const {
    cout << __PRETTY_FUNCTION__ << '\n';
    for (int q = 0; q < N; ++q) {
      for (int w = 1; q + w < N + 1; ++w) {
        string_view pat(s.data() + q, w);
        cout << "pat: " << pat << '\t';
        testcase(st.has_substr(pat), true);
        st.has_substr(pat);

        string fail_s = string(pat) + string(1, 'a' + 27);
        cout << "fail_pat: " << fail_s << '\t';
        st.has_substr(fail_s);
        testcase(st.has_substr(fail_s), false);

        string fail_s2 = string(pat.substr(0, pat.size() / 2)) +
                         string(1, 'a' + 27) +
                         string(pat.substr(pat.size() / 2));
        cout << "fail_pat: " << fail_s2 << '\t';
        st.has_substr(fail_s2);
        testcase(st.has_substr(fail_s2), false);
      }
    }
    testcase(st.has_substr(""), true);
  }

 private:
  string_view s;
  const int N;
  SuffixTree<27, 'a'> st;
};

int main(int argc, char** argv) {
  string x = argv[1] ? argv[1] : "";
  string y = argv[2] ? argv[2] : "";

  if (!x.empty()) {
    x += "$"; // add unique char
    SuffixTree<256, '\0'> st(x);
    st.print();
    string xx(begin(x), end(x) - 1);
    // auto lps = SuffixTree<256, '\0'>::lps(xx);
    // cout << "lps of '" << x << "' is '" << lps << "'\n";
    bool ok = st.has_substr(y);
    cout << "st '" << x << "' has substring '" << y << "': " << boolalpha << ok
         << '\n';
    auto v = st.search_all(y);
    cout << "st '" << x << "' has substring idx of '" << y << "': " << v
         << '\n';
    y += "#"; // add unique char
    auto lrs = st.lrs();
    cout << "st '" << x << "' has lrs '" << lrs << "'\n";
    auto lcs = SuffixTree<256, '\0'>::lcs(x, y);
    cout << "lcs of (" << x << ", " << y << ") is '" << lcs << "'\n";
    return 0;
  }

  for (auto s : {"abcabcdcabx", "aaaaa", "babaabaaabaaaabaaaaa", "",
                 "aababcabcdabcde", "aaabaabaaa"}) {
    string x{s};
    Test test(x);
    test.test_substr();
    test.test_lcs();
    string y = x + string(1, 'a' + 26);  // append unique char
    Test test2(y);
    test2.test_search_all();
    test2.test_lrs();
  }
  for (auto [a, b, exp] : {tuple{"azaxzaz", "bcccbbbzabcccbb", "za"},
                           {"qwerxreqxrqe", "rewqxrqxereq", "qxrq"},
                           {"", "", ""},
                           {"a", "", ""},
                           {"", "a", ""},
                           }) {
    auto lcs = SuffixTree<28, 'a'>::lcs(a, b);
    testcase(lcs, exp);
  }
  // for (auto [a, exp] : {tuple{"bcabeffbacb", "ff"},
  //                          {"babeffbab", "bab"},
  //                          {"", ""},
  //                          {"abacdfgdcaba", "aba"},
  //                          }) {
  //   auto lps = SuffixTree<256, '\0'>::lps(a);
  //   testcase(lps, exp);
  // }
}
