def to_sets(args):
    return [{x} for x in args]


def f(args):
    print('args', args)
    args = to_sets(args)

    def f_(args):
        if not args:
            return {}
        if len(args) == 1:
            return args[0]
        new = [x ^ y for x, y in zip(args, args[1:])]
        # print(new)
        return f_(new)
    return f_(args)


def shuffle(args):
    return args[::2] + args[1::2]


if __name__ == '__main__':
    # ans = []
    # n = 2 ** 5 + 1
    # for i in range(1, n + 1):
    #     a = f(list(range(1, i + 1)))
    #     print(sorted(a))
    #     ans.append(a)
    #     print('-' * 40)

    cards = list(range(1, 2 ** 5 + 1))

    def sorthalf(cds):
        return sorted(cds[:len(cds) // 2])
    print(sorthalf(cards))
    n = 17
    for _ in range(17):
        cards = shuffle(cards)
        print(sorthalf(cards))
