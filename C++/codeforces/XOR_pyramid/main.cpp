#include <stdio.h>
#include <algorithm>

using namespace std;
int MOD = 8;
int num[5004];
int dp[5004][5004];
int mdp[5004][5004];
int main() {
    int n, q;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", num + i);
    for (int i = 1; i < n + 1; ++i) { // i = length
        for (int j = 0; j < n - i + 1; ++j) {
            if (i == 1) {
              dp[j][j] = num[j];
              mdp[j][j] = num[j];
            } else if (i == 2) {
              dp[j][j + 1] = num[j] ^ num[j + 1];
              mdp[j][j + 1] = max({num[j] ^ num[j + 1], num[j], num[j + 1]});
            } else if (i % 2 == 0) {
              dp[j][j + i - 1] = dp[j][j + i - 3] ^ num[j + i - 2] ^ num[j + i - 1];
              mdp[j][j + i - 1] = max({mdp[j][j + i],
                  mdp[j + 1][j + i - 1], dp[j][j + i - 1]});
            } else {
              dp[j][j + i - 1] = num[j] ^ num[j + i - 1];
              mdp[j][j + i - 1] = max({mdp[j][j + i],
                  mdp[j + 1][j + i - 1], dp[j][j + i - 1]});
            }
        }
    }
    for (int i = 0; i < n; ++i) { // i = length
        for (int j = 0; j < n; ++j) {
          printf("%d ", mdp[i][j]);
        }
        printf("\n");
    }


    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
       int l, r;
       scanf("%d %d", &l, &r);
       l--, r--;
       printf("%d\n", mdp[l][r]);
    }
    return 0;
}
