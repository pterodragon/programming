import itertools
import random
import matplotlib.pyplot as plt


def min_step(m):
    ls = list(itertools.chain.from_iterable(m))
    return min(abs(x - y) for x, y in zip(ls, ls[1:]))


def is_kaccept(m, k):
    ls = list(itertools.chain.from_iterable(m))
    return all(abs(x - y) >= k for x, y in zip(ls, ls[1:]))


def findk(m):
    k = 0
    perm = m
    for rs in itertools.permutations(m):
        ms = min_step(rs)
        if ms > k:
            k = max(k, ms)
            perm = rs
    return k, perm


def subsumes(r1, r2):  # r1 subsumes r2
    a, b = r1
    c, d = r2
    return a <= c and b >= d


def max_list_subsumes(ls1, ls2):
    # all segs of ls1 subsumes at least 1 of ls2
    return all(any(subsumes(r1, r2) for r2 in ls2) for r1 in ls1)


def min_subsume_set(ls):
    s = []
    for r1 in ls:
        if any(subsumes(r1, r2) for r2 in s):
            continue
        s = [r2 for r2 in s if not subsumes(r2, r1)]
        s.append(r1)
    return s


def max_list_subsume_set(ls):
    s = []
    for r1 in ls:
        if any(max_list_subsumes(r2, r1) for r2 in s):
            continue
        s = [r2 for r2 in s if not max_list_subsumes(r1, r2)]
        s.append(r1)
    return s


def max_list_subsume_set_n(n):
    sort_key = lambda r: (abs(r[0] - r[1]), r[0])
    s = set()
    for perm in itertools.permutations(range(n)):
        ls = [sorted(x) for x in zip(perm, perm[1:])]
        ls.sort()
        ls_rs = min_subsume_set(ls)
        ls_rs.sort(key=sort_key)
        ls_rs = tuple(tuple(x) for x in ls_rs)
        s.add(ls_rs)
    s = max_list_subsume_set(s)
    return s


if __name__ == '__main__':
    # r, c = map(int, input().split())
    # m = [[int(x) for x in input().split()] for _ in range(r)]
    # print(r, c)
    # print(m)

    n = 9
    def dprint(*args, debug=True, **kwargs):
        if debug:
            print(*args, **kwargs)

#     for _ in range(10):
#         rrs = [[random.randrange(10)] for _ in range(n)]
#         rrs.sort()
#         dprint(rrs)
#         k, perm = findk(rrs)
#         dprint('k =', k)
#         dprint('perm =', perm)
#         res = max(min(abs(a[0] - b[0]) for a, b in segs) for segs in itertools.combinations(list(zip(rrs, rrs[n // 2:])), n // 2))
#         dprint('res =', res)
#         if res == k:
#             print('OK')
#         print('---')
#     exit()

    s = max_list_subsume_set_n(n)
    y = 0
    print('max', s)
    # exit()
    for t in s:
        for a, b in t:
            plt.plot((a, b), (y, y), marker='o')
            y += 1
        y += 2
        plt.plot((0, n - 1), (y, y), color='gray', linestyle='--')
        y += 2
    # plt.yticks(range(len(s)))
    plt.title(f'n = {n}')
    plt.show()
