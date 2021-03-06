from operator import mul
from functools import reduce
from copy import deepcopy


def extract_factor(n, f):
    a = 0
    while n % f == 0:
        n /= f
        a += 1
    return a


def subtract_from_list(l, d):
    for e, i in enumerate(l):
        l[e], d = max(0, i - d), max(0, d - i)
        if d == 0:
            break
    assert d == 0, 'should have enough to subtract'


def solve(size1, size2):
    sizes = [list(size1), list(size2)]
    factor2 = [[extract_factor(n, 2) for n in s] for s in sizes]
    factor3 = [[extract_factor(n, 3) for n in s] for s in sizes]
    base = [[x // 2 ** y // 3 ** z for x, y, z in zip(s, f2, f3)] for s, f2, f3 in zip(sizes, factor2, factor3)]

    if reduce(mul, base[0]) != reduce(mul, base[1]):
        return

    factor2_total = [sum(x for x in f2) for f2 in factor2]
    factor3_total = [sum(x for x in f3) for f3 in factor3]

    d3 = factor3_total[0] - factor3_total[1]
    prev_factor3 = deepcopy(factor3)
    i = (1, 0)[d3 > 0]
    subtract_from_list(factor3[i], abs(d3))
    factor2_total[i] += abs(d3)
    factor2[i][0] += (prev_factor3[i][0] - factor3[i][0])
    factor2[i][1] += (prev_factor3[i][1] - factor3[i][1])

    d2 = factor2_total[0] - factor2_total[1]
    l = factor2[(1, 0)[d2 > 0]]
    subtract_from_list(l, abs(d2))

    size_after = tuple(
            tuple(x * (2 ** y) * (3 ** z) for x, y, z in zip(b, f2, f3)) for b, f2, f3 in zip(base, factor2, factor3))
    return abs(d3) + abs(d2), size_after[0], size_after[1]


if __name__ == '__main__':
    size1 = tuple(int(x) for x in raw_input().split())
    size2 = tuple(int(x) for x in raw_input().split())
    ans = solve(size1, size2)
    if ans is None:
        print -1
    else:
        m, s1, s2 = ans
        print m
        print s1[0], s1[1]
        print s2[0], s2[1]
