from solution import Solution


def test():
    res = Solution().findUnsortedSubarray([2, 6, 4, 8, 10, 9, 15])
    assert res == 5
    res = Solution().findUnsortedSubarray([6, 6, 4, 8, 10, 9, 15])
    assert res == 6
    res = Solution().findUnsortedSubarray([2, 4, 4, 8, 10, 9, 15])
    assert res == 2
    res = Solution().findUnsortedSubarray([1,2,3,4])
    assert res == 0
