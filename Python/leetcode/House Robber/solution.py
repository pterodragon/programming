class Solution(object):

    def rob(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        p, q = 0, 0  # previous no rob, previous rob
        for e in nums:
            p, q = max(p, q), p + e
        return max(p, q)
