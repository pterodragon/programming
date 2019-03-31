#ifndef DSUF_HPP
#define DSUF_HPP

#include <algorithm>
#include <vector>

using namespace std;
/*
 * reference:
 * https://github.com/spaghetti-source/algorithm/blob/master/data_structure/union_find.cc
 */

/*
 * Disjoint Set Union Find
 */
class DSUF {
 public:
  DSUF(int n) : p(n, -1) {}

  // with path compression
  int root(int i) { return p[i] < 0 ? i : p[i] = root(p[i]); }

  bool same_set(int i, int j) { return root(i) == root(j); }

  void uni(int u, int v) {
    u = root(u);
    v = root(v);
    if (u == v) return; // erase this if no check
    if (p[u] > p[v]) swap(u, v);
    p[u] += p[v];
    p[v] = u;
  }

  int size(int u) { return -p[root(u)]; }

 private:
  vector<int> p;  // parents (and negative size(/rank) for roots)
};

#endif /* DSUF_HPP */
