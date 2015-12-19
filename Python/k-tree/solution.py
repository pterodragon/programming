from pprint import pprint

n, k, d = (int(x) for x in raw_input().split())

if n < d:
    print 0
    exit()

dp = [[0 for x in xrange(k + 1)] for y in xrange(n + 1)]

for j in xrange(k + 1):
    for i in xrange(n + 1):
        if i == 0:
            dp[i][j] = 1
        elif j == 0:
            dp[i][j] = 0
        elif i > j:
            dp[i][j] = dp[i][j - 1] + dp[i - j][j]
        elif i == j:
            dp[i][j] = 1

pprint(dp)
pprint('ans = {}'.format(dp[-1][-1]))
