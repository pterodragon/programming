/*
 * Reference: https://codeforces.com/blog/entry/16780
 */
#ifndef SUFFIX_TREE2_HPP
#define SUFFIX_TREE2_HPP

#include <climits>
#include <map>
#include <vector>

using namespace std;

class SuffixTree2 {
  using state = unsigned;

  string_view s;
  const unsigned N;
  static constexpr const unsigned ROOT = 0, INF = UINT_MAX;
  vector<map<char, state> > g; // transitions // use array for O(n) build time
  vector<unsigned> f;  // suffix links // doesn't matter what f[0] is
  struct RP {
    unsigned lp = 0, len = INF;
  };
  vector<RP> rps;  // rps[v]: left pointer, len from non-self closest ancestor
  state q = 1;

 public:
  void print() const;

  SuffixTree2(string_view s)
      : s(s), N(s.size()), g(2 * N + 1), f(2 * N + 1), rps(2 * N + 1) {
    for (unsigned i = 0, actl = 1, actn = 0; i < N; ++i, ++actl)
      update(i, actn, actl);  // active node, active length
  }

  void update(unsigned i, unsigned& actn, unsigned& actl) {
    int last = 0;
    while (actl > 0) {
      while (actl > rps[g[actn][s[i - actl + 1]]].len) {  // canonize
        actn = g[actn][s[i - actl + 1]];
        actl -= rps[actn].len;
      }
      unsigned& v = g[actn][s[i - actl + 1]];  // 't'-transition from actn
      char next = s[rps[v].lp + actl - 1];  // char right after "active point"
      if (v == 0) {  // implies actl == 1 ;  no such 't'-transition
        rps[v = q++] = {i - actl + 1, INF};
        f[last] = actn;
        last = ROOT;  // prevent modifying f[last]; split won't happen after
      } else if (next == s[i]) {  // extend active length
        f[last] = actn;
        return;
      } else {
        unsigned u = q;
        rps[q++] = {rps[v].lp, actl - 1};
        g[u][s[i]] = q;
        rps[q++] = {i, INF};
        g[u][next] = v;
        rps[v].lp += actl - 1;   // ancestor lp is now position of new node (u)
        rps[v].len -= actl - 1;  // update length from ancestor
        v = u;                   // actn's 't'-transition is now to u
        f[last] = u;
        last = u;
      }
      if (actn == ROOT)
        --actl;
      else
        actn = f[actn];
    }
  }
};

#endif /* SUFFIX_TREE2_HPP */
