class Solution:
    def findLongestChain(self, pairs):
        """
        :type pairs: List[List[int]]
        :rtype: int
        """

        """
        sort pairs first
        only choose the smallest pairs if they have the same first element
        i.e. [1,2] and [1,10], delete the [1, 10]

        dp[x] = longest chain that uses pair on index x
        solution = dp[n - 1]
        dp[0] = 1
        dp[a + 1] = max(dp[x] for x in range(a + 1) \
            if pairs[x][1] < pairs[a + 1][0])
        """
        if not pairs:
            return 0

        pairs.sort()
        n = len(pairs)
        dp = [1 for _ in range(n)]
        dp[0] = 1
        for a in range(1, n):
            for b in reversed(range(a)):
                if pairs[b][1] < pairs[a][0]:
                    dp[a] = dp[b] + 1
                    break
        return dp[n - 1]
