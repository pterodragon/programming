def run(n, b):
    if len(b) % 2:
        return 0
    v = []
    x = 0
    for c in b:
        x += (1 if c == '(' else -1)
        v.append(x)
        if x < -2:
            return 0
    if x not in (2, -2):
        return 0
    if x == -2:
        pass


def brute_force(n, b):
    if len(b) % 2:
        return 0
    res = 0
    for i, c in enumerate(b, 1):
        c = '(' if c == ')' else ')'
        new = b[:i - 1] + c + b[i:]
        ok = check_ok(new)
        res += ok

    return res


def check_ok(b):
    x = 0
    for c in b:
        x += (1 if c == '(' else -1)
        if x < 0:
            return False
    return x == 0


if __name__ == '__main__':
    n = int(input())
    b = input()
    print(brute_force(n, b))
