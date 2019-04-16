from typing import List


class Solution:
    def thirdMax(self, nums: List[int]) -> int:
        a, b, c = -float('inf'), -float('inf'), -float('inf')
        for e in nums:
            if e > a:
                a, b, c = e, a, b
            if e == a:
                continue
            if e > b:
                b, c = e, b
            if e == b:
                continue
            if e > c:
                c = e
        return a if c == -float('inf') else c
