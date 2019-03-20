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
