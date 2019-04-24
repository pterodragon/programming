from solution import Solution


def test():
    assert Solution().reachNumber(-1) == 1
    assert Solution().reachNumber(0) == 0
    assert Solution().reachNumber(1) == 1
    assert Solution().reachNumber(2) == 3  # 6 - 2 * 2
    assert Solution().reachNumber(3) == 2
    assert Solution().reachNumber(4) == 3  # 6 - 1 * 2
    assert Solution().reachNumber(5) == 5  # 15 - 5 * 2
    assert Solution().reachNumber(6) == 3
    assert Solution().reachNumber(7) == 5  # 15 - 4 * 2
    assert Solution().reachNumber(8) == 4  # 10 - 1 * 2
    assert Solution().reachNumber(9) == 5  # 15 - 3 * 2
    assert Solution().reachNumber(10) == 4  # 10
