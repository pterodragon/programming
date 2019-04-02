#ifndef SUFFIX_ARRAY_HPP
#define SUFFIX_ARRAY_HPP

#include <algorithm>
#include <array>
#include <numeric>
#include <string_view>
#include <vector>

#include <iostream>
#include "prettyprint.hpp"

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

/*
 * note
 * 1:   Just to be pedantic, if the char is a negative value then there's a
 *      problem during counting
 * 2:   ra size is 2 * N just to avoid the annoying bound checks like
 *      sa[i] + k < N etc.; values defaulted to be 0
 */
template <unsigned Alph = 128, char SC = '\0'>  // |Sigma|, start char
class SuffixArray {
 public:
  SuffixArray(string_view sv)
      : sv(sv), N(sv.length()), ra(2 * N), sa(N) {  // see note 2
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
  inline void counting_sort(int k, vector<int>& temp) {
    array<int, Alph> c{};
    for (int i = 0; i < N; ++i) ++c[ra[i + k]];
    partial_sum(begin(c), end(c), begin(c));
    for (int i = N - 1; i >= 0; --i)
      temp[--c[ra[sa[i] + k]]] = sa[i];

    sa = temp;
  }

  void construct() {
    vector<int> temp(N);
    for (int i = 0; i < sv.size(); ++i)
      ra[i] = (unsigned char)sv[i] - SC;  // see note 1
    iota(begin(sa), end(sa), 0);
    for (int k = 1; k < N; k <<= 1) {
      counting_sort(k, temp);
      counting_sort(0, temp);
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
template <unsigned Alph, char SC>
template <char UC>
string_view SuffixArray<Alph, SC>::lcs(string_view s1, string_view s2) {
  static_assert(Alph > (unsigned char)(UC - SC));
  auto cat = string(s1) + UC + string(s2);
  auto sa = SuffixArray<Alph, SC>(cat);
  auto lcp = sa.lcp();
  auto is_s1 = [&sa, m = s1.size()](int q) { return sa.sa[q] < m; };
  int z = 0;
  for (int q = 1; q < sa.N; ++q)
    if (lcp[q] > lcp[z] && is_s1(q - 1) != is_s1(q)) z = q;

  return s1.substr(z ? sa.sa[z - (sa.sa[z] > s1.size())] : 0, lcp[z]);
}

template <unsigned Alph, char SC>
void SuffixArray<Alph, SC>::print() const {
  for (int i = 0; i < N; ++i) printf("%2d|\t%s\n", sa[i], sv.data() + sa[i]);
}

/*
 * search for a pattern in O(m log(n)) time where
 * m is the length of the pattern
 * n is the length of the text which a suffix array is built for
 *
 * return the indices of all the occurrence of the pattern
 */
template <unsigned Alph, char SC>
vector<int> SuffixArray<Alph, SC>::binary_search(string_view pat) const {
  if (empty(pat) || pat.size() > N) return {0, 0};
  auto it_l = lower_bound(cbegin(sa), cend(sa), pat, [this](auto a, auto pat) {
    return sv.substr(a) < pat;
  });
  auto it_r = upper_bound(cbegin(sa), cend(sa), pat, [this](auto pat, auto a) {
    auto [it1, it2] = mismatch(cbegin(pat), end(pat), cbegin(sv) + a, cend(sv));
    return it2 == cend(sv) || *it1 < *it2;
  });
  return vector(it_l, it_r);
}

/*
 * Construct the Longest Common Prefix array from the current suffix array
 * LCP[0] = 0, LCP[i] = longest common prefix of sa[i] and sa[i - 1]
 */
template <unsigned Alph, char SC>
vector<int> SuffixArray<Alph, SC>::lcp() const {
  auto plcp_ = plcp();
  vector<int> lcp(N);
  for (int i = 0; i < N; i++) lcp[i] = plcp_[sa[i]];
  return lcp;
}

/*
 * Construct the Permuted Longest Common Prefix array
 * from the current suffix array
 * PLCP[sa[i]] = LCP[i]
 *
 * PLCP theorm: PLCP[i] >= PLCP[i - 1] - 1 (see notes.md)
 */
template <unsigned Alph, char SC>
vector<int> SuffixArray<Alph, SC>::plcp() const {
  vector<int> phi(N);  // phi[i] index of previous suffix of sa[i]
  vector<int> plcp(N);
  phi[sa[0]] = -1;
  for (int i = 1; i < N; ++i) phi[sa[i]] = sa[i - 1];
  for (int i = 0, L = 0; i < N; ++i) {
    if (phi[i] == -1) continue;  // i = sa[0]; PLCP[sa[0]] = LCP[0] = 0
    while (sv[i + L] == sv[phi[i] + L]) ++L;
    plcp[i] = L;  // sa[x] = i, plcp[sa[x]] = L
    L = max(L - 1, 0);
  }
  return plcp;
}

/*
 * return (a, count) of the longest repeated substring in sa
 * where sv[a:a+count] is the lrs
 */
template <unsigned Alph, char SC>
pair<int, int> SuffixArray<Alph, SC>::lrs() const {
  auto lcp_ = lcp();
  auto it = max_element(begin(lcp_), end(lcp_));
  return {sa[distance(begin(lcp_), it)], *it};
}

#endif /* SUFFIX_ARRAY_HPP */
