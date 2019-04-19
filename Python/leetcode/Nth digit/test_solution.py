from solution import Solution


def test():
    res = Solution().findNthDigit(3)
    assert res == 3
    res = Solution().findNthDigit(11)
    assert res == 0
    res = Solution().findNthDigit(9 + 90 * 2 + 1)
    assert res == 1
    res = Solution().findNthDigit(9 + 90 * 2 + 900 * 3 + 1)
    assert res == 1
    res = Solution().findNthDigit(9 + 90 * 2 + 900 * 3 + 5)  # 1001
    assert res == 1
    res = Solution().findNthDigit(9 + 90 * 2 + 900 * 3 + 6)  # 1001
    assert res == 0
    res = Solution().findNthDigit(9 + 90 * 2 + 900 * 3 + 7)  # 1001
    assert res == 0
    res = Solution().findNthDigit(9 + 90 * 2 + 900 * 3 + 8)  # 1001
    assert res == 1
