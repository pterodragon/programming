# from pprint import pprint

n = int(raw_input())
intervals = []
adj_list = []
for i in xrange(n):
    qtype, x, y = raw_input().split()
    x, y = int(x), int(y)
    if qtype == '1':
        neighbors = []
        for idx, itv in enumerate(intervals):
            if x < itv[0] < y or x < itv[1] < y:
                adj_list[idx].append(len(intervals))
            if itv[0] < x < itv[1] or itv[0] < y < itv[1]:
                neighbors.append(idx)
        adj_list.append(neighbors)
        intervals.append((x, y))
    else:
        x, y = x - 1, y - 1  # switch to 0 index
        visited = [False for _ in range(len(intervals))]
        stack = [x]
        visited[x] = True
        success = False
        while stack:
            node_idx = stack.pop()
            for idx in adj_list[node_idx]:
                if y == idx:
                    success = True
                    break
                if not visited[idx]:
                    stack.append(idx)
                    visited[idx] = True
        print 'YES' if success else 'NO'

# pprint(intervals)
# pprint(adj_list)
