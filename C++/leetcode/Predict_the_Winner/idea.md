### Given
    nums: an array of int; length = L

### States of problem
    int dp[L][L];
    dp[r][s] = max win score margin (P1 score - P2 score) got from subarray nums[r:s + 1] (up to and including nums[s]; Python slice)
            for r, s in [0, L - 1]

### Answer
    dp[0][L - 1] >= 0
    score margin from nums[0:L] >= 0

### Recursion
    dp[a][a] = nums[a]; for a in [0, L - 1]
    dp[r][s] = max(nums[r] - dp[r + 1][s], nums[s] - dp[r][s - 1])

### Help
