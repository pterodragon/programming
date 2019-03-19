#include "suffix_array.hpp"
#include <cstdio>

void SuffixArray::print() const {
  for (int i = 0; i < n; ++i) printf("%2d|\t%s\n", sa[i], sv.data() + sa[i]);
}
