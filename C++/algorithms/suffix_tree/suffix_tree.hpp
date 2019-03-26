// This implements:
// E. Ukkonen, "On-line construction of suffix trees," Algorithmica, vol. 14,
// pp. 249-260, 1995.
//
// Implementation is as close to the pseudocode in the paper as possible
#include <array>
#include <string_view>
#include <tuple>
#include <vector>

using namespace std;

// AlphabetSize (default is small letters); SC = Start char
template <int Alph = 26, char SC = 'a'>
class SuffixTree {
  static const constexpr int BOTTOM = 0, ROOT = 1;
  using state = int;

  // (s, (k, _)) reference pair (without right pointer)
  using RP = pair<state, int>;

  // (k, p, s') from g(s, (k, p)) = s'
  using GT = tuple<int, int, state>;

 public:
  void print() const;
  bool has_substr(string_view pat) const;
  // ----------------------------------------

  // A suffix tree has at most n - 1 branching states; at most 2 * n - 2
  // transitions; at most 2 * n states
  //
  // This implementation uses 2 * n + 2 for the bounds,
  // + 2 just to guard the empty string case: f[ROOT] = BOTTOM
  SuffixTree(string_view sv)
      : t(sv), N(sv.length()), q_count(2), f(2 * N + 2), g(2 * N + 2) {
    algorithm2();
  }

 private:
  void algorithm2() {
    // XXX: CAUTION! string is now 0 indexed, i and k should start from 0
    // and max string index = n - 1
    for (int j = 0; j < Alph; ++j) g[BOTTOM][j] = {-j, -j, ROOT};
    f[ROOT] = BOTTOM;
    for (int i = 0, s = ROOT, k = 0; i < N; ++i) {
      tie(s, k) = update(s, k, i);
      tie(s, k) = canonize(s, k, i);
    }
  }

  RP update(state s, int k, int i) {
    state oldr = ROOT;
    auto [is_end_point, r] = test_and_split(s, k, i - 1, t[i]);
    while (!is_end_point) {
      g[r][t[i] - SC] = {i, N - 1, q_count++};
      if (oldr != ROOT) f[oldr] = r;
      oldr = r;
      tie(s, k) = canonize(f[s], k, i - 1);
      tie(is_end_point, r) = test_and_split(s, k, i - 1, t[i]);
    }
    if (oldr != ROOT) f[oldr] = s;
    return {s, k};
  }

  pair<bool, state> test_and_split(state s, int k, int p, char t_) {
    if (k <= p) {
      auto [kp, pp, sp] = g[s][t[k] - SC];
      if (t_ == t[kp + p - k + 1]) return {true, s};

      state r = q_count++;
      g[s][t[k] - SC] = {kp, kp + p - k, r};
      g[r][t[kp + p - k + 1] - SC] = {kp + p - k + 1, pp, sp};
      return {false, r};
    }
    return {g[s][t_ - SC] != GT{}, s};
  }

  RP canonize(state s, int k, int p) const {
    if (p < k) return {s, k};

    auto [kp, pp, sp] = g[s][t[k] - SC];
    while (pp - kp <= p - k) {
      k += pp - kp + 1;
      s = sp;
      if (k <= p) tie(kp, pp, sp) = g[s][t[k] - SC];
    }
    return {s, k};
  }

  string_view t;
  const int N;    // length of string
  state q_count;  // state indices
  vector<state> f;  // suffix links

  // transitions; g[s][i] = {k, p, r}
  // -> state#s 't[i]'-transition is
  // g(s, (k, p)) = r
  // where t[k] = t[i]
  //
  // to save space, using a map/hash is also possible
  vector<array<GT, Alph> > g;
};

template <int Alph, char SC>
bool SuffixTree<Alph, SC>::has_substr(string_view pat) const {
  if (pat.empty()) return true;

  state s = ROOT;
  int i = 0;
  while (true) {
    auto [kp, pp, sp] = g[s][pat[i] - SC];
    if (sp == 0) return false;
    auto len = pp - kp + 1;
    int len_check = min((int)pat.size() - i, len);
    if (t.substr(kp, len_check) != pat.substr(i, len_check)) return false;
    i += len;
    if (i >= pat.size()) return true;
    s = sp;
  };
}

#include <iostream>
template <int Alph, char SC>
void SuffixTree<Alph, SC>::print() const {
  cout << "f: ";
  for (state q = 0; q < 2 * N; ++q) {
    if (f[q]) printf("f[%d] = %d | ", q, f[q]);
  }
  cout << '\n';
  cout << "g: ";
  for (state q = 1; q < 2 * N; ++q) {
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
