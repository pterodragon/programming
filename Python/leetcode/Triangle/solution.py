class Solution(object):

    def minimumTotal(self, triangle):
        """
        :type triangle: List[List[int]]
        :rtype: int
        """
        dp = [0]
        for row in triangle:
            dp = [v + min(dp[max(0, j - 1):j + 1])
                  for j, v in enumerate(row)]
        return min(dp)
