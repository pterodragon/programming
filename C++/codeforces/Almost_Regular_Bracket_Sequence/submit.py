def run(b):
    if len(b) % 2:
        return 0
    vs = []
    v = 0
    for c in b:
        v += (1 if c == '(' else -1)
        if v < -2:
            return 0
        vs.append(v)
    end = vs[-1]
    if end not in (2, -2):
        return 0
    if end == 2:
        if any(x < 0 for x in vs):
            return 0
        res = 0
        for i in reversed(range(len(b))):
            v, c = vs[i], b[i]
            if v < 2:
                break
            if c == '(':
                res += 1
        return res
    else:
        res = 0
        for i, (v, c) in enumerate(zip(vs, b)):
            if v < -1:
                break
            if c == ')':
                res += 1
            if v == -1:
                break
        return res


if __name__ == '__main__':
    n = input()
    s = input()
    res = run(s)
    print(res)
