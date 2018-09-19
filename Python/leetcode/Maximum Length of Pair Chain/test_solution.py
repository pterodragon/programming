import solution
import nose  # NOQA


def test():
    s = solution.Solution()
    test_cases = (
        ([[1, 10], [2, 3], [4, 5], [6, 7], [8, 11]], 4),
        ([[2, 3], [4, 5], [8, 11], [6, 7], [1, 10]], 4),
        ([], 0),
        ([[1, 2]], 1),
    )
    for test, expected in test_cases:
        actual = s.findLongestChain(test)
        assert actual == expected
