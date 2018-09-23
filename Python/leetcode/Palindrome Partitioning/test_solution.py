import solution
import nose  # NOQA


def test():
    tests = [
        ['abba', {('a', 'b', 'b', 'a'), ('a', 'bb', 'a'), ('abba', )}],
        ['aaa', {('a', 'a', 'a'), ('a', 'aa'), ('aa', 'a'), ('aaa', )}],
        ['aab', {('aa', 'b'), ('a', 'a', 'b')}],
        ['a', {('a', )}],
        ['aa', {('a', 'a'), ('aa', )}]
    ]

    def lol_to_tot(l):
        return tuple(lol_to_tot(x) if isinstance(x, list) else x for x in l)

    for t, ans in tests:
        actual = solution.Solution().partition(t)
        assert set(lol_to_tot(actual)) == ans, \
            'failed test: input = {}; expected = {}; actual = {}'.format(
                t, ans, actual)
