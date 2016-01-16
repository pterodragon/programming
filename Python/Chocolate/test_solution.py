import solution


def test_solve():
    case = (36, 5), (10, 16)
    m, s1, s2 = solution.solve(case[0], case[1])
    assert s1[0] * s1[1] == s2[0] * s2[1]

    case = (40, 5), (150, 36)
    m, s1, s2 = solution.solve(case[0], case[1])
    assert s1[0] * s1[1] == s2[0] * s2[1]

    case = (2160, 3240), (7200, 384)
    m, s1, s2 = solution.solve(case[0], case[1])
    assert s1[0] * s1[1] == s2[0] * s2[1] == 640 * 2160
    assert m == 5


def test_subtract_from_list():
    l = [1, 3, 4, 5]
    solution.subtract_from_list(l, 6)
    assert l == [0, 0, 2, 5]
