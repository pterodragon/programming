#ifndef SUFFIX_ARRAY_HPP
#define SUFFIX_ARRAY_HPP

#include <algorithm>
#include <array>
#include <numeric>
#include <string_view>
#include <vector>

using namespace std;

// https://gist.github.com/markormesher/7e3b39028f7e7237b098ebf35dcd6545
/*
 * Prefix doubling: O(n log n) construction time
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
 * In this implementation, counting sort the 2^k'th column first and then sort
 * the 0'th column (k = 1, 2, 3,...) will result in R1, R2, R4
 */

#include <iostream>
#include "prettyprint.hpp"

class SuffixArray {
 public:
  SuffixArray(string_view sv) : sv(sv), N(sv.length()), ra(N), sa(N) {
    construct();
  }

  void print() const;
  vector<int> binary_search(string_view sv) const;
  vector<int> lcp() const;
  vector<int> plcp() const;
  pair<int, int> lrs() const;

  template <char UC = '$'>
  static string_view lcs(string_view s1, string_view s2);

 private:
  // stable sort is necessary
  // using std::stable_sort to skip this but increase complexity
  inline void counting_sort(int k) {
    vector<int> temp(N);
    array<int, 256> c{};
    for (int i = 0; i < N; ++i) ++c[i + k < N ? ra[i + k] : 0];
    partial_sum(begin(c), end(c), begin(c));
    for (int i = N - 1; i >= 0; --i)
      temp[--c[sa[i] + k < N ? ra[sa[i] + k] : 0]] = sa[i];

    sa = temp;
  }

  void construct() {
    vector<int> temp(N);
    copy(begin(sv), end(sv), begin(ra));
    iota(begin(sa), end(sa), 0);
    for (int k = 1; k < N; k <<= 1) {
      counting_sort(k);
      counting_sort(0);
      temp[sa[0]] = 1;  // r (rank) starts from 1 below; sa[i] + k > n => rank 0
      for (int i = 1, r = 1; i < N; ++i) {  // rerank
        r += ra[sa[i]] != ra[sa[i - 1]] || ra[sa[i] + k] != ra[sa[i - 1] + k];
        temp[sa[i]] = r;
      }
      ra = temp;
      if (ra[sa[N - 1]] == N) break;  // all rank different => finished
    }
  }

  const string_view sv;

 public:
  const int N;

 private:
  vector<int> ra;  // rank array
  vector<int> sa;  // suffix array
};

/*
 * return (a, b) of the longest common substring of s1, s2
 * where s1[a:a+b] is the lcs
 *
 * WARNING: s1 and s2 cannot have the UC (unique char)
 */
template <char UC>
string_view SuffixArray::lcs(string_view s1, string_view s2) {
  auto cat = string(s1) + UC + string(s2);
  auto sa = SuffixArray(cat);
  auto lcp = sa.lcp();
  auto is_s1 = [&sa, m = s1.size()](int q) { return sa.sa[q] < m; };
  int z = 0;
  for (int q = 1; q < sa.N; ++q)
    if (lcp[q] > lcp[z] && is_s1(q - 1) != is_s1(q)) z = q;

  return s1.substr(sa.sa[z - (sa.sa[z] > s1.size())], lcp[z]);
}
#endif /* SUFFIX_ARRAY_HPP */
