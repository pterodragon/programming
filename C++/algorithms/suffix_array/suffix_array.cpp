#include "suffix_array.hpp"
#include <cstdio>
#include <iostream>
#include <iterator>
#include <sstream>

void SuffixArray::print() const {
  for (int i = 0; i < n; ++i) printf("%2d|\t%s\n", sa[i], sv.data() + sa[i]);
}

/*
 * search for a pattern in O(m log(n)) time where
 * m is the length of the pattern
 * n is the length of the text which a suffix array is built for
 *
 * return the index of one of the first occurence of a pattern
 * -1 if pattern is not found
 */
int SuffixArray::binary_search(string_view pat) const {
  if (empty(pat)) return -1;
  auto sit = cbegin(pat);
  auto it =
      upper_bound(cbegin(sa), cend(sa), pat, [this, &sit](auto pat, auto a) {
        auto [it1, it2] =
            mismatch(cbegin(sv) + a, cend(sv), cbegin(pat), end(pat));
        bool ok = it2 == cend(sv) || *it1 >= *it2;
        if (ok) sit = it2;
        return ok;
      });
  return sit == cend(pat) ? *it : -1;
}

/*
 * Construct the Longest Common Prefix array from the current suffix array
 * LCP[0] = 0, LCP[i] = longest common prefix of sa[i] and sa[i - 1]
 */
vector<int> SuffixArray::lcp() const {
  auto plcp_ = plcp();
  vector<int> lcp(n);
  for (int i = 0; i < n; i++) lcp[i] = plcp_[sa[i]];
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
  vector<int> phi(n);  // phi[i] index of previous suffix of sa[i]
  vector<int> plcp(n);
  phi[sa[0]] = -1;
  for (int i = 1; i < n; ++i) phi[sa[i]] = sa[i - 1];
  for (int i = 0, L = 0; i < n; ++i) {
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

/*
 * return (a, b) of the longest common substring of s1, s2
 * where s1[a:a+b] is the lcs
 */
pair<int, int> SuffixArray::lcs(string_view s1, string_view s2) {
  // s1 and s2 cannot have '$'
  auto sa = SuffixArray(string(s1) + '$' + string(s2));
  auto lcp = sa.lcp();
  auto is_s1 = [&sa, m = s1.size()](int q) { return sa.sa[q] < m; };
  int z = 0;
  for (int q = 1; q < sa.n; ++q)
    if (lcp[q] > lcp[z] && is_s1(q) && !is_s1(q - 1)) z = q;
  return {sa.sa[z], lcp[z]};  // z < s1.size()
}
