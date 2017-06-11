import solution
import nose


def test():
    s = solution.Solution()
    tests = (((3, 5, 1), 5),
             ((), 0),
             ((100,), 100),
             )
    for t, ans in tests:
        actual = s.rob(t)
        assert actual == ans, 'failed test: input = {}; expected = {}; actual = {}'.format(t, ans, actual)
