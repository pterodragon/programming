// This implements:
// E. Ukkonen, "On-line construction of suffix trees," Algorithmica, vol. 14,
// pp. 249-260, 1995.
//
// Implementation is as close to the pseudocode in the paper as possible
#include <array>
#include <string_view>
#include <tuple>
#include <vector>
#include <algorithm>

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
  vector<int> search_all(string_view pat) const;
  string_view lrs() const;
  string_view lrs_dfs() const;
  static string_view lcs(string_view sa, string_view sb);
  static string_view lps(string_view sb);
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
  const int N;      // length of string
  state q_count;    // state indices
  vector<state> f;  // suffix links

  // transitions; g[s][i] = {k, p, r}
  // -> state#s 't[i]'-transition is
  // g(s, (k, p)) = r
  // where t[k] = t[i]
  //
  // to save space, using a map/hash is also possible
  vector<array<GT, Alph>> g;
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

/*
 * return all indices of occurrence of pat
 * return {} if pat is empty
 *
 * WARNING: The suffix tree must be built with a string appended with a unique
 * character. Otherwise this function will return a wrong result
 */
template <int Alph, char SC>
vector<int> SuffixTree<Alph, SC>::search_all(string_view pat) const {
  if (pat.empty() || !has_substr(pat)) return {};
  state s = ROOT;
  int i = 0;
  auto [kp, pp, sp] = GT{};
  while (i < (int)pat.size()) {
    tie(kp, pp, sp) = g[s][pat[i] - SC];
    i += pp - kp + 1;
    s = sp;
  };
  if (pp == N - 1) return {kp - (i - (pp - kp + 1))};

  vector<int> res;
  vector<pair<state, int>> q{{sp, i}};

  while (!q.empty()) {  // BFS
    auto [s, i] = q.back();
    q.pop_back();
    for (int c = 0; c < Alph; ++c) {
      auto [kp, pp, sp] = g[s][c];
      if (pp == N - 1)
        res.push_back(kp - i);
      else if (sp != 0)
        q.push_back({sp, i + pp - kp + 1});
    }
  };
  return res;
}

/*
 * Longest repeated substring
 *
 * This returns one of the lrs
 *
 * WARNING: The suffix tree must be built with a string appended with a unique
 * character. Otherwise this function will return a wrong result
 */
template <int Alph, char SC>
string_view SuffixTree<Alph, SC>::lrs() const {
  using T = tuple<int, int, state>;  // len, idx, state
  T res{0, 0, ROOT};
  vector<T> q{res};  // start idx and length

  while (!q.empty()) {  // BFS
    auto [len, _, s] = q.back();
    q.pop_back();
    for (int c = 0; c < Alph; ++c) {
      auto [kp, pp, sp] = g[s][c];
      if (pp == N - 1)
        res = max(res, {len, kp, s});
      else if (sp != 0)
        q.push_back({len + pp - kp + 1, kp, sp});
    }
  };
  auto [len, i, _] = res;
  return t.substr(i - len, len);
}

/*
 * Just another lrs implementation by using dfs because you can
 * and it's shorter
 *
 * WARNING: The suffix tree must be built with a string appended with a unique
 * character. Otherwise this function will return a wrong result
 */
template <int Alph, char SC>
string_view SuffixTree<Alph, SC>::lrs_dfs() const {
  using T = tuple<int, int>;  // len, idx
  auto dfs = [this](T res, state s, auto f) -> T {
    auto len = get<0>(res);
    for (int c = 0; c < Alph; ++c) {
      if (auto [kp, pp, sp] = g[s][c]; sp != 0)
        res = max(res,
                  pp == N - 1 ? T{len, kp} : f({len + pp - kp + 1, kp}, sp, f));
    }
    return res;
  };
  auto [len, i] = dfs({0, 0}, ROOT, dfs);
  return t.substr(i - len, len);
}

/*
 * Longest common substring
 *
 * WARNING: SC + Alph - 1 and SC + Alph - 2 will be used as unique characters
 */
template <int Alph, char SC>
string_view SuffixTree<Alph, SC>::lcs(string_view sva, string_view svb) {
  string sa = string(sva) += char(SC + Alph - 1);
  string sb = string(svb) += char(SC + Alph - 2);
  string s = sa + sb;
  SuffixTree st(s);
  using T = tuple<int, int>;  // len, idx, state
  using U = pair<int, T>;     // belongs to, T
  auto dfs = [&st, N_1 = sa.size()](T res, state s, auto f) -> U {
    auto len = get<0>(res);
    int b = 0;
    for (int c = 0; c < Alph; ++c) {
      if (auto [kp, pp, sp] = st.g[s][c]; sp != 0) {
        if (kp < N_1 && pp > N_1) pp = N_1 - 1;
        int z = (pp == st.N - 1) | (pp == N_1 - 1) * 2;
        if (z) {
          b |= z;
          res = max(res, {len, kp});
        } else {
          auto [b_recur, res_recur] = f({len + pp - kp + 1, kp}, sp, f);
          if (b_recur == 3) res = max(res, res_recur);
          b |= b_recur;
        }
      }
    }
    return {b, res};
  };
  auto [b, res] = dfs({0, 0}, ROOT, dfs);
  auto [len, i] = res;
  if (b != 3) return sa.substr(0, 0);
  bool first = i - len < sa.size();
  return (first ? sva : svb).substr(i - len - (first ? 0 : sa.size()), len);
}

// #include "prettyprint.hpp"
// /*
//  * Longest palindromic substring
//  *
//  * WARNING: SC + Alph - 1 and SC + Alph - 2 will be used as unique characters
//  */
// template <int Alph, char SC>
// string_view SuffixTree<Alph, SC>::lps(string_view sva) {
//   cout << "###\n";
//   // string sa = string(sva) += char(SC + Alph - 1);
//   string sa = string(sva) += '#';
//   string sb;
//   sb.reserve(sva.size() + 1);
//   reverse_copy(begin(sva), end(sva), back_inserter(sb));
//   // sb += char(SC + Alph - 2);
//   sb += '@';
//   string s = sa + sb;
//   SuffixTree st(s);
//   st.print();
// 
//   vector<int> pos;
//   auto dfs = [&st, &pos, N = s.size(), N_1 = sa.size()](int len, state s, auto f) -> int {
//     cout << "--------------------\n";
//     for (int c = 0; c < Alph; ++c) {
//       if (auto [kp, pp, sp] = st.g[s][c]; sp != 0) {
//         if (kp < N_1 && pp > N_1) pp = N_1 - 1;
//         int z = (pp == st.N - 1) | (pp == N_1 - 1) * 2;
//         cout << "# kp: " << kp << ", len: " << len << '\n';
//         if (z) {
//           // res = max(res, {len, kp});
//           cout << "kp: " << kp << ", len: " << len << '\n';
//           int kp_other;
//           if (kp > N_1) {
//             kp_other = N_1 - 1 - (kp - N_1) + len;
//             if (pos[kp_other]) {
//               cout << "pos[" << kp_other << "] = " << pos[kp_other] << '\n';
//               res = max(res, {len, kp});
//             } else {
//               pos[kp] = len;
//             }
//           } else {
//             kp_other = N_1 - 1 - kp + len;
//             if (pos[kp_other]) {
//               cout << "pos[" << kp_other << "] = " << pos[kp_other] << '\n';
//               res = max(res, {len, kp});
//             } else {
//               pos[kp] = len;
//             }
//           }
//           cout << "kp: " << kp << ", len: " << len << ", kp_other: " << kp_other << '\n';
//         } else {
//           auto [b_recur, res_recur] = f({len + pp - kp + 1, kp}, sp, f);
//           if (b_recur == 3) {
//             cout << "res_recur: " << res_recur << '\n';
//             res = max(res, res_recur);
//           }
//         }
//       }
//     }
//     return {b, res};
//   };
//   auto [b, res] = dfs({0, 0}, ROOT, dfs);
//   auto [len, i] = res;
//   if (b != 3) return sa.substr(0, 0);
//   bool first = i - len < sa.size();
//   cout << "res: " << res << '\n';
//   if (first) {
//     return sva.substr(i - len, len);
//   } else {
//     return sva.substr(i - len - sa.size() + 1, len);
//   }
// }

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
