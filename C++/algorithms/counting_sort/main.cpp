#include "counting_sort.hpp"
#include <iostream>

int main() {
  string str = "hellozzaz";
  vector strv(begin(str), end(str));
  counting_sort_inplace(strv);
  for (auto c: strv) cout << c << ' '; 
  cout << '\n';

  vector vstr{"adc", "bad", "cba", "dcb"};
  auto cs = [&vstr](int idx) {
    return counting_sort(vstr, [idx](auto const& str) { return str[idx]; } );
  };
  auto cs2 = [&vstr](int idx) {
    return counting_sort2(vstr, [idx](auto const& str) { return str[idx]; } );
  };
  for (size_t i = 0; i < 3; ++i) {
    for (auto const& e: cs(i)) {
      cout << e << '\t';
    }
    cout << '\n';
  }
  for (size_t i = 0; i < 3; ++i) {
    for (auto const& e: cs2(i)) {
      cout << e << '\t';
    }
    cout << '\n';
  }
}
