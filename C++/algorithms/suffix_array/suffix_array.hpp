#ifndef SUFFIX_ARraY_HPP
#define SUFFIX_ARraY_HPP

#include <array>
#include <string_view>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// https://gist.github.com/markormesher/7e3b39028f7e7237b098ebf35dcd6545
/*
 * Prefix doubling
 *
 * s = banana
 * R2[i] = rank of the pair (R1[i], R1[i + 1])
 * R4[i] = rank of the pair (R2[i], R2[i + 2])
 *
 * R1  R2         R4
 * 0:  1   1,0 -> 2   2,3 -> 3
 * 1:  0   0,2 -> 1   1,1 -> 2
 * 2:  2   2,0 -> 3   3,3 -> 5
 * 3:  0   0,2 -> 1   1,0 -> 1
 * 4:  2   2,0 -> 3   3,* -> 4
 * 5:  0   0,* -> 0   0,* -> 0
 *           ^
 *           |
 *           |-- Just shift from R2
 *
 *         ^ ^ requires 2 counting sorts anyway
 *
 * In this implementation, counting sort the 2^k'th column first and then sort the 0'th column (k = 1, 2, 3,...) will result in R1, R2, R4
 */
class SuffixArray {
 public:
  SuffixArray(string_view sv) : sv(sv), n(sv.length()), ra(n), sa(n), temp(n) {
    construct();
  }

  void print() const;
  int binary_search(string_view sv) const;
  vector<int> lcp() const;
  vector<int> plcp() const;
  pair<int, int> lrs() const;

 private:
  // stable sort is necessary
  // using std::stable_sort to skip this but increase complexity
  void counting_sort(int k) {
    c.fill(0);
    for (int i = 0; i < n; ++i) ++c[i + k < n ? ra[i + k] : 0];
    partial_sum(begin(c), end(c), begin(c));
    for (int i = n - 1; i >= 0 && i < n; --i)
      temp[--c[sa[i] + k < n ? ra[sa[i] + k]: 0]] = sa[i];

    sa = temp;
  }

  void construct() {
    copy(begin(sv), end(sv), begin(ra));
    iota(begin(sa), end(sa), 0);
    for (int k = 1; k < n; k <<= 1) {
      counting_sort(k);
      counting_sort(0);
      temp[sa[0]] = 0;
      for (int i = 1, r = 0; i < n; ++i) {  // rerank
        r += ra[sa[i]] != ra[sa[i - 1]] || ra[sa[i] + k] != ra[sa[i - 1] + k];
        temp[sa[i]] = r;
      }
      ra = temp;
      if (ra[sa[n - 1]] == n - 1) break;  // all rank different => finished
    }
  }

  string_view sv;
  int n;
  array<int, 256> c;
  vector<int> ra; // rank array
  vector<int> sa; // suffix array
  vector<int> temp;
};

#endif /* SUFFIX_ARraY_HPP */
