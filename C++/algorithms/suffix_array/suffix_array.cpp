#include "suffix_array.hpp"
#include <cstdio>
#include <iostream>
#include <iterator>
#include <sstream>

void SuffixArray::print() const {
  for (int i = 0; i < N; ++i) printf("%2d|\t%s\n", sa[i], sv.data() + sa[i]);
}

/*
 * search for a pattern in O(m log(n)) time where
 * m is the length of the pattern
 * n is the length of the text which a suffix array is built for
 *
 * return the indices of all the occurrence of the pattern
 */
vector<int> SuffixArray::binary_search(string_view pat) const {
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
vector<int> SuffixArray::lcp() const {
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
vector<int> SuffixArray::plcp() const {
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
pair<int, int> SuffixArray::lrs() const {
  auto lcp_ = lcp();
  auto it = max_element(begin(lcp_), end(lcp_));
  return {sa[distance(begin(lcp_), it)], *it};
}
