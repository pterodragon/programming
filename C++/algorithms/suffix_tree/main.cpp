#include "suffix_tree.hpp"

#include <cassert>
#include <iomanip>

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
  Test(string_view s) : s(s), st(s) {}

  void test_substr() const {
    cout << "--- s: " << s << '\n';
    for (int q = 0; q < s.size(); ++q) {
      for (int w = 1; q + w < s.size(); ++w) {
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
  SuffixTree<27, 'a'> st;
};

int main(int argc, char** argv) {
  string x = argv[1] ? argv[1] : "";
  string y = argv[2] ? argv[2] : "";

  if (!x.empty()) {
    SuffixTree<256, '\0'> st(x);
    st.print();
    bool ok = st.has_substr(y);
    cout << "st '" << x << "' has substring '" << y << "': " << boolalpha << ok
         << '\n';
    return 0;
  }

  for (auto s : {"abcabcdcabx", "aaaaa", "babaabaaabaaaabaaaaa", "",
                 "aababcabcdabcde"}) {
    string x{s};
    Test test(x);
    test.test_substr();
  }
}
