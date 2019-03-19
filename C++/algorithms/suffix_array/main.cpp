#include <iostream>
#include <string>

#include "suffix_array.hpp"

using namespace std;

int main() {
  string T = "babaabaaabaaaab";
  int n = T.size();
  printf("n: %d\n", n);
  T[n] = '$';
  T[++n] = '\0';
  SuffixArray sa(T);
  sa.print();
}
