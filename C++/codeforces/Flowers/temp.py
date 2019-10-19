# z/k
# generated the possible sequences

import argparse


def gen_combination(z, k):
    if z <= 0:
        yield ''
        return
    for s in gen_combination(z - 1, k):
        yield 'r' + s
    if z >= k:
        for s in gen_combination(z - k, k):
            yield k * 'w' + s


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('z', type=int)
    parser.add_argument('k', type=int)
    args = parser.parse_args()
    z, k = args.z, args.k
    print(z, k)

    for x in gen_combination(z, k):
        print(x)

    for a in range(1, z + 1):
        for b in range(1, k + 1):
            print(str(len(list(gen_combination(a, b)))).rjust(4), end=' ')
        print()
