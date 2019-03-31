#include <cassert>
#include <iostream>

#include "dsuf.hpp"

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

void test_dsuf() {
  const int n = 16;
  DSUF dsuf(n);
  for (int q = 0; q < n; ++q) {
    testcase(dsuf.size(q), 1);
  }
  for (int q = 0; q < n; q += 2) {
    dsuf.uni(q, q + 1);
  }
  for (int q = 0; q < n; q += 2) {
    testcase(dsuf.same_set(q, q + 1), true);
    testcase(dsuf.size(q), 2);
    testcase(dsuf.size(q + 1), 2);
  }
  for (int q = 0; q < n; q += 4) {
    testcase(dsuf.same_set(q, q + 1), true);
    testcase(dsuf.same_set(q, q + 2), false);
    testcase(dsuf.same_set(q, q + 3), false);
    testcase(dsuf.same_set(q + 1, q + 2), false);
    testcase(dsuf.same_set(q + 1, q + 3), false);
    testcase(dsuf.same_set(q + 2, q + 3), true);
  }
  for (int q = 0; q < n; q += 4) {
    dsuf.uni(q, q + 2);
  }
  for (int q = 0; q < n; q += 4) {
    testcase(dsuf.same_set(q, q + 1), true);
    testcase(dsuf.same_set(q, q + 2), true);
    testcase(dsuf.same_set(q, q + 3), true);
    testcase(dsuf.same_set(q + 1, q + 2), true);
    testcase(dsuf.same_set(q + 1, q + 3), true);
    testcase(dsuf.same_set(q + 2, q + 3), true);
    testcase(dsuf.size(q), 4);
    testcase(dsuf.size(q + 1), 4);
    testcase(dsuf.size(q + 2), 4);
    testcase(dsuf.size(q + 3), 4);
  }
}

int main() { test_dsuf(); }
