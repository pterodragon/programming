#include <string>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        const size_t L = s.size();
        stack<int> k;
        vector<int> e(L, 0); // e[i] longest valid parens string ends at index i (inclusive)
        int m = 0;
        for (size_t i = 0; i < L; ++i) {
            const char c = s[i];
            if (c == '(') {
                k.push(i);
            } else if (!k.empty()) {
                int top = k.top();
                k.pop();
                e[i] += (i - top + 1);
                if (top > 0) {
                    e[i] += e[top - 1];
                }
                m = max(m, e[i]);
            }
        }
        return m;
    }
};
