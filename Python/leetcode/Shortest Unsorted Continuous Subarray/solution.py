from typing import List
from itertools import accumulate


class Solution:
    def findUnsortedSubarray(self, nums: List[int]) -> int:
        min_from_right = list(reversed(list(accumulate(reversed(nums), min))))
        max_from_left = list(accumulate(nums, max))
        try:
            a = next(i for i, (x, y) in enumerate(
                zip(nums, min_from_right)) if x != y)
        except StopIteration:
            return 0
        b = next(
            i for i, (x, y)
            in reversed(list(enumerate(zip(nums, max_from_left))))
            if x != y)
        return b - a + 1
