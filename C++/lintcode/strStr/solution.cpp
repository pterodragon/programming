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
            puts(__PRETTY_FUNCTION__);
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
                    q = pi[q - 1];
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
            puts(__PRETTY_FUNCTION__);
            int m = strlen(p);
            vector<int> pi(m);
            int k = 0;
            for (int q = 1; q < m; ++q) {
                //printf("q = %d\n", q);
                while (k > 0 && p[k] != p[q]) {
                    k = pi[k - 1];
                }
                if (p[k] == p[q]) {
                    ++k;
                }
                pi[q] = k;
                //printf("pi[%d] = %d\n", q, k);
            }
            print_prefix(pi, p);
            return pi;
        }

        void print_prefix(const vector<int>& pi, const char* p) {
            puts(__PRETTY_FUNCTION__);
            for (int i = 0; i < pi.size(); ++i) {
                printf("%c, ", p[i]);
            }
            puts("");
            for (int i = 0; i < pi.size(); ++i) {
                printf("%d, ", pi[i]);
            }
            puts("");
        }
};

int main() {
    array<tuple<string, string, int>, 7> a{{
        make_tuple("aabaabcd", "abaabc", 1), 
            make_tuple("cabaaabaabbb", "aaabaababa", -1),
            make_tuple("aaabaaaabaaabaababa", "aaaabaaabaabab", 4),
            make_tuple("zabcdefgzabcdefg", "abcdefgabcdefabcde", -1),
            make_tuple("aaaaab", "aab", 3),
            make_tuple("zzzzzzzzzz", "zzzzzzzzzz", 0),
            make_tuple("aaabbbccc", "abbbc", 2),
    }};

    for (auto p : a) {
        int ans = Solution().strStr(get<0>(p).c_str(), get<1>(p).c_str());
        printf("t=%s, p=%s, first substring index = %d; assert = %d\n", get<0>(p).c_str(), get<1>(p).c_str(), ans, get<2>(p));
        if (ans != get<2>(p)) {
            printf("-------------------\n");
            printf("--- TEST FAILED ---\n");
            printf("-------------------\n");
        }
        puts("---");
    }
    return 0;
}
