import solution
import nose


def test():
    tests = [
        [[[-10]], -10],
        [[[-10], [1, 2]], -9],
             [[
                 [2],
                 [3, 4],
                 [6, 5, 7],
                 [4, 1, 8, 3]
                 ],
              11]
             ]
    for t, ans in tests:
        actual = solution.Solution().minimumTotal(t)
        assert actual == ans, \
            'failed test: input = {}; expected = {}; actual = {}'.format(
                t, ans, actual)
