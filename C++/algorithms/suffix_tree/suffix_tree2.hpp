#ifndef SUFFIX_TREE2_HPP
#define SUFFIX_TREE2_HPP

#define debug_print(x) cout << #x << ": " << x << '\n'

#include <bits/stdc++.h>

using namespace std;

struct ST {
  const int inf = 1e9;
  static constexpr int maxn = 30;
  char s[maxn];
  vector<map<char, int> > to;
  int len[maxn] = {}, ffpos[maxn] = {}, link[maxn] = {};
  int node = 0, pos = 0;
  int sz = 1, n = 0;

  ST(string s) : to(maxn) {
    len[0] = inf;
    for (int i = 0; i < s.size(); i++) {
      // cout << "#################### i = " << i << "\n";
      add_letter(s[i]);
    }
    // This calculates total length of all edges
    int ans = 0;
    for (int i = 1; i < sz; i++) ans += min((int)s.size() - ffpos[i], len[i]);
    // cout << ans << "\n";
  }

  int make_node(int _pos, int _len) {
    ffpos[sz] = _pos;
    len[sz] = _len;
    return sz++;
  }

  void go_edge() {  // canonize? (node, (ffpos[node], ffpos[node] + pos - 1))?
                    // is a canonical reference pair
    while (pos > len[to[node][s[n - pos]]]) {
      node = to[node][s[n - pos]];
      pos -= len[node];
    }
  }

  void add_letter(char c) {
    s[n++] = c;
    pos++;  // active length?
    int last = 0;
    while (pos > 0) {
      // cout << "c: " << c << "; n: " << n << "; pos: " << pos << "; node: " << node << "; last: " << last << '\n';
      go_edge();
      char edge = s[n - pos];  // 'edge'-transition
      // cout << "edge: " << edge << '\n';
      int& v = to[node][edge];  // active point
      // cout << "v: " << v << '\n';
      char t = s[ffpos[v] + pos - 1];  // character of the active point
      // cout << "t: " << t << '\n';
      // cout << "---\n";
      if (v == 0) {
        // cout << "@@@ v == 0\n";
        v = make_node(n - pos, inf);  // new active point is v // v is ref
        link[last] = node;
        last = 0;
      } else if (t == c) {
        // cout << "@@@ t == c \n";
        link[last] = node;
        return;
      } else {
        // cout << "@@@ other\n";
        int u = make_node(ffpos[v], pos - 1);
        to[u][c] = make_node(n - 1, inf);
        to[u][t] = v;
        ffpos[v] +=
            pos - 1;  // update the ancestor to be position of new node (u)
        len[v] -= pos - 1;  // update length from ancestor
        v = u;              // node' edge-transition is now to u
        link[last] = u;
        last = u;
      }
      if (node == 0)
        pos--;
      else
        node = link[node];
    }
  }

  void print2() {
    cout << "f: ";
    for (int i = 0; i < sz; ++i) {
      if (len[i] < inf / 2) printf("f[%d] = %d | ", i, link[i]);
    }
    cout << '\n';
    cout << "g: ";
    for (int i = 0; i < sz; ++i) {
      for (auto [k, v] : to[i]) {
        // printf("[%c -> %d] ", k, v);
        printf("g(%d, [%c](%d, %d)) = %d | ", i, k, ffpos[v], (len[v] > inf / 2) ? n - 1 : (ffpos[v] + len[v] - 1), v);
      }
    }
    cout << '\n';
    // cout << "ffpos: \n";
    // for (int i = 0; i < sz; ++i) cout << setw(2) << ffpos[i] << ' ';
    // cout << '\n';
    // cout << "link: \n";
    // for (int i = 0; i < sz; ++i) cout << setw(2) << link[i] << ' ';
    // cout << '\n';
    // cout << "len: \n";
    // for (int i = 0; i < sz; ++i) cout << setw(2) << (len[i] > inf / 2 ? -1 :
    // len[i]) << ' '; cout << '\n'; for (int i = 0; i < sz; ++i) {
    //   printf("to[%d]: ", i);
    //   for (auto [k, v] : to[i]) {
    //     printf("[%c -> %d] ", k, v);
    //   }
    //   cout << '\n';
    // }
  }

  void print() {
    for (int i = 0; i < sz; ++i) cout << setw(2) << i << ' ';
    cout << '\n';
    cout << "ffpos: \n";
    for (int i = 0; i < sz; ++i) cout << setw(2) << ffpos[i] << ' ';
    cout << '\n';
    cout << "link: \n";
    for (int i = 0; i < sz; ++i) cout << setw(2) << link[i] << ' ';
    cout << '\n';
    cout << "len: \n";
    for (int i = 0; i < sz; ++i)
      cout << setw(2) << (len[i] > inf / 2 ? -1 : len[i]) << ' ';
    cout << '\n';
    for (int i = 0; i < sz; ++i) {
      printf("to[%d]: ", i);
      for (auto [k, v] : to[i]) {
        printf("[%c -> %d] ", k, v);
      }
      cout << '\n';
    }
  }
};

int main(int argc, char** argv) {
  ST st(argv[1]);
  // st.print();
  st.print2();
}

#endif /* SUFFIX_TREE2_HPP */
