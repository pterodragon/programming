#include <iostream>
#include "counting_sort.hpp"

int main() {
  string str = "hellozzaz";
  vector strv(begin(str), end(str));
  counting_sort_inplace(strv);
  for (auto c : strv) cout << c << ' ';
  cout << '\n';

  vector<string> vstr(27, "aaa");
  for (int q = 0; q < 3; ++q)
    for (int w = 0; w < 3; ++w)
      for (int e = 0; e < 3; ++e)
          vstr[q + w * 3 + e * 9][0] += q,
              vstr[q + w * 3 + e * 9][1] += w,
              vstr[q + w * 3 + e * 9][2] += e;
  // radix sort
  for (int i = 0; i <= 2; ++i) {
    vstr = counting_sort(vstr, [i](auto const& str) { return str[i]; });
  }
  for (auto s: vstr) cout << s << '\n';
  cout << '\n';
  for (int i = 2; i >= 0; --i) {
    vstr = counting_sort2(vstr, [i](auto const& str) { return str[i]; });
  }
  for (auto s: vstr) cout << s << '\n';
}
