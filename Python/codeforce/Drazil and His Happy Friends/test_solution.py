import solution


def test_solve():
    cases = (
        (('2 3', '0', '1 0'), 'Yes'),
        (('2 3', '1 0', '1 1'), 'Yes'),
        (('2 4', '1 0', '1 2'), 'No'),
        (('4 6', '2 0 1', '0'), 'Yes'),
        (('4 6', '1 0', '0'), 'No'),
    )
    for test, ans in cases:
        n, m = [int(x) for x in test[0].split()]
        b = [int(x) for x in test[1].split()]
        g = [int(x) for x in test[2].split()]
        assert solution.solve(n, m, b, g) == ans, "wrong for case: {}".format(test)
