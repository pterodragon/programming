class Solution(object):

    def rob(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        # [1:] case: 0th rob; [2:-1] case: 0th no rob
        def f(n, p):
            q = p
            for e in n:
                p, q = max(p, q), p + e
            return max(p, q)
        return max(f(nums[1:], 0), f(nums[2:-1], nums[0])) if nums else 0
