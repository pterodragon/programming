import fractions


def solve(n, m, b, g):
    nhb, hb = b[0], b[1:] if b else []
    nhg, hg = g[0], g[1:] if g else []
    happy = [False] * (m + n)
    for i in hb:
        happy[i] = True
    for j in hg:
        happy[n + j] = True

    gcd = fractions.gcd(n, m)
    if gcd == 1:
        print 'Yes' if nhb + nhg > 0 else 'No'
        return 'Yes' if nhb + nhg > 0 else 'No'

    lcm = n * m / gcd
    adj_list = [[] for _ in xrange(m + n)]
    visited = [False] * (n + m)
    for i in xrange(lcm):
        adj_list[i % n].append(n + i % m)
        adj_list[n + i % m].append(i % n)

    # print '-' * 100
    # print 'happy = {}'.format(happy)
    # print '(n, m, b, g) = ({}, {}, {}, {})'.format(n, m, b, g)
    # print 'lcm={}'.format(lcm)
    # print 'adj_list:'
    # print adj_list
    # print 'Status:'
    # print happy

    for i in xrange(n + m):
        if visited[i]:
            continue
        girls_happy = 0
        boys_happy = 0
        stack = [i]
        visited[i] = True
        while stack:
            a = stack.pop()
            # print 'poped {}'.format(a)
            if happy[a]:
                if a > n:
                    girls_happy += 1
                else:
                    boys_happy += 1
            happy[a] = True
            for j in adj_list[a]:
                if not visited[j]:
                    visited[j] = True
                    stack.append(j)
                    # print 'appended {}'.format(j)
        if girls_happy + boys_happy == 0:
            print 'No'
            return 'No'
            # print 'girls happy: {}, boys_happy: {}'.format(girls_happy, boys_happy)
            # print 'Status:'
            # print happy

    print 'No' if not all(happy) else 'Yes'
    return 'No' if not all(happy) else 'Yes'


n, m = [int(x) for x in raw_input().split()]
b = [int(x) for x in raw_input().split()]
g = [int(x) for x in raw_input().split()]

solve(n, m, b, g)
