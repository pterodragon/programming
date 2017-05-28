def to_base3(i, w, shift=False):
    l = []
    for _ in range(w):
        l = [i % 3 + (-1 if shift else 0)] + l
        i //= 3
    return l


def solve(w, n):
    i = sum(3 ** x for x in range(101))
    j = 2 * i
    l = tuple(w ** x for x in range(100, -1, -1))
    while i <= j:  # as usual binary search is hard to implement ._.
        m = (i + j) // 2
        a = to_base3(m, 101, True)
        s = sum(x * y for x, y in zip(a, l))
        if s == n:
            return True
        elif n > s:
            i = m + 1
        else:
            j = m - 1
    return False


if __name__ == '__main__':
    w, n = [int(x) for x in raw_input().split()]
    print 'YES' if solve(w, n) else 'NO'
