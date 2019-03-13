// This implements:
// E. Ukkonen, "On-line construction of suffix trees," Algorithmica, vol. 14,
// pp. 249-260, 1995.
//
// Implementation is as close to the pseudocode in the paper as possible
#include <array>
#include <iostream>
#include <string_view>
#include <tuple>
#include <vector>

using namespace std;

using state = int;

// (s, (k, _)) reference pair (without right pointer)
using RP = pair<state, int>;

// (k, p, s') from g(s, (k, p)) = s'
using GT = tuple<int, int, state>;

// AlphabetSize (default is small letters); SC = Start char
template <int Alph = 26, char SC = 'a'>
class SuffixTree {
  static constexpr int BOTTOM = 0;
  static constexpr int ROOT = 1;

 public:
  void print() const;
  // ----------------------------------------

  // A suffix tree has at most n - 1 branching states; at most 2 * n - 2
  // transitions; at most 2 * n states
  //
  // This implementation uses 2 * n + 1 for the bounds,
  // + 1 just to guard the empty string case
  SuffixTree(string_view sv)
      : t(sv), n(sv.length()), q_count(2), f(2 * n + 1), g(2 * n + 1) {
    algorithm2();
  }

 private:
  void algorithm2() {
    // XXX: CAUTION! string is now 0 indexed, i and k should start from 0
    // and max string index = n - 1
    int s = ROOT, k = 0;
    for (int j = 0; j < Alph; ++j) g[BOTTOM][j] = {-j, -j, ROOT};
    f[ROOT] = BOTTOM;
    for (int i = 0; i < n; ++i) {
      tie(s, k) = update(s, k, i);
      tie(s, k) = canonize(s, k, i);
    }
  }

  RP update(int s, int k, int i) {
    int oldr = ROOT;
    auto [is_end_point, r] = test_and_split(s, k, i - 1, t[i]);
    while (!is_end_point) {
      g[r][t[i] - SC] = {i, n - 1, q_count++};
      if (oldr != ROOT) f[oldr] = r;
      oldr = r;
      tie(s, k) = canonize(f[s], k, i - 1);
      tie(is_end_point, r) = test_and_split(s, k, i - 1, t[i]);
    }
    if (oldr != ROOT) f[oldr] = s;
    return {s, k};
  }

  pair<bool, int> test_and_split(int s, int k, int p, char t_) {
    if (k <= p) {
      auto [kp, pp, sp] = g[s][t[k] - SC];
      if (t_ == t[kp + p - k + 1]) return {true, s};

      int r = q_count++;
      g[s][t[k] - SC] = {kp, kp + p - k, r};
      g[r][t[kp + p - k + 1] - SC] = {kp + p - k + 1, pp, sp};
      return {false, r};
    }
    return {g[s][t_ - SC] != GT{}, s};
  }

  RP canonize(int s, int k, int p) const {
    if (p < k) return {s, k};

    auto [kp, pp, sp] = g[s][t[k] - SC];
    while (pp - kp <= p - k) {
      k = k + pp - kp + 1;
      s = sp;
      if (k <= p) tie(kp, pp, sp) = g[s][t[k] - SC];
    }
    return {s, k};
  }

  string_view t;
  int n;  // length of string
  int q_count; // state indices
  vector<int> f;  // suffix links

  // transitions; g[s][i] = {k, p, r}
  // -> state#s 't[i]'-transition is
  // g(s, (k, p)) = r
  // where t[k] = t[i]
  //
  // to save space, using a map/hash is also possible
  vector<array<GT, Alph> > g;
};

template <int Alph, char SC>
void SuffixTree<Alph, SC>::print() const {
  cout << "f: ";
  for (int q = 0; q < 2 * n; ++q) {
    if (f[q]) printf("f[%d] = %d | ", q, f[q]);
  }
  cout << '\n';
  cout << "g: ";
  for (int q = 1; q < 2 * n; ++q) {
    for (int w = 0; w < Alph; ++w) {
      auto tup = g[q][w];
      if (tup != GT{}) {
        auto [kp, pp, sp] = tup;
        printf("g(%d, [%c](%d, %d)) = %d | ", q, t[kp], kp, pp, sp);
      }
    }
  }
  cout << '\n';
}

