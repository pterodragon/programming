#include <bits/stdc++.h>

using namespace std;

class Solution {
    public:
        /**
         * Returns a index to the first occurrence of target in source,
         * or -1  if target is not part of source.
         * @param t string to be scanned.
         * @param p string containing the sequence of characters to match.
         */
        int strStr(const char *t, const char *p) {
            if (t == nullptr || p == nullptr) {
                return -1;
            }
            int n = strlen(t);
            int m = strlen(p);
            if (m == 0) {
                return 0;
            }
            auto pi = prefix(p);
            int q = 0;
            for (int i = 0; i < n; ++i) {
                while (q > 0 && p[q] != t[i]) {
                    q = pi[q];
                }
                if (p[q] == t[i]) {
                    ++q;
                }
                if (q == m) {
                    return i - m + 1;
                }
            }
            return -1;
        }

        vector<int> prefix(const char* p) {
            int m = strlen(p);
            vector<int> pi(m);
            int k = 0;
            for (int q = 1; q < m; ++q) {
                while (k > 0 && p[k] != p[q]) {
                    k = pi[k];
                }
                if (p[k] == p[q]) {
                    ++k;
                }
                pi[q] = k;
            }
            return pi;
        }
};

int main() {
    int ans = Solution().strStr("abcdabcdefg", "bcd");
    printf("ans = %d\n", ans);
}
