#include "suffix_array.hpp"
#include <cstdio>
#include <iostream>
#include <iterator>

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
 * PLCP theorm: PLCP[i] >= PLCP[i - 1] - 1
 * meaning PLCP can at most decrease 1 one step at a time
 *
 * Proof:
 * Let sa[x] = 0 => T[sa[x]:] = T[0:] = T
 * Let sa[y] = 1 => T[sa[y]:] = T[1:]
 *
 * Since length of T[sa[x]:] is 1 more than T[sa[y]:] and
 * PLCP[sa[x]] = PLCP[0] = LCP[x] referring to (sa[x], sa[x - 1]) = (0, ?)
 * PLCP[sa[y]] = PLCP[1] = LCP[y] referring to (sa[y], sa[y - 1]) = (1, ??)
 *
 * let LCP[x] = q > 1 (if q = 0 or 1 then PLCP[0] = 0 or 1,
 *                     PLCP[1] >= PLCP[1 - 1] - 1 = -1 or 0)
 * say
 * T[sa[x]:] = T[0:] = T = t0  t1      ...t(q - 1)    ...tn
 * T[sa[x - 1]:] =         t(z)t(z + 1)...t(z + q - 1)...tn
 * where t(x)t(x + 1)...t(x + q - 1) = t0t1...t(q - 1)
 * and T[sa[x - 1]:] is lexicographically smaller than T[sa[x]:]
 *
 * losing length of 1 starting from index 1,
 * T[sa[y]:] = T[1:] = T = t1t2...t(q - 1)...tn
 * T[sa[y - 1]:] must have a prefix t1t2...t(q - 1) starting from another index
 * because there is at least one string W = T[sa[x - 1] + 1:] which spells that
 * prefix and W is lexicographically smaller than T[sa[y]:]
 *
 * same argument applies for sa[x] = a, sa[y] = a + 1
 */
vector<int> SuffixArray::plcp() const {
  vector<int> phi(n); // phi[i] index of previous suffix of sa[i]
  vector<int> plcp(n);
  phi[sa[0]] = -1;
  for (int i = 1; i < n; ++i) phi[sa[i]] = sa[i - 1];
  for (int i = 0, L = 0; i < n; ++i) {
    if (phi[i] == -1) continue; // phi[sa[0](=i)] == -1; PLCP[sa[0]] = LCP[0] = 0
    while (sv[i + L] == sv[phi[i] + L]) ++L;
    plcp[i] = L; // sa[x] = i, plcp[sa[x]] = L
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
