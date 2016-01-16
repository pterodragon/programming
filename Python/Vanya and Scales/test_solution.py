import solution


def test_tobase3():
    x = '102'
    y = int(x, 3)
    assert solution.to_base3(y, 3) == list(int(e) for e in x)
    x = '1' * 101
    y = int(x, 3)
    assert solution.to_base3(y, 101) == list(int(e) for e in x)


def test_solve():
    assert solution.solve(3, 3213314) is True
    assert solution.solve(2, 3213314) is True
    assert solution.solve(2, 3213314) is True
    assert solution.solve(100, 50) is False
