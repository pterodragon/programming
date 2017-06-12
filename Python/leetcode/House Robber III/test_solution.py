import solution
from solution import TreeNode
import nose


def list_to_binary_tree(ls):
    nodes = [None if x is None else TreeNode(x) for x in ls]
    N = len(ls)
    for i in range(N):
        if (i + 1) * 2 - 1 < N:
            nodes[i].left = nodes[(i + 1) * 2 - 1]
        if (i + 1) * 2 < N:
            nodes[i].right = nodes[(i + 1) * 2]
    return nodes[0] if ls else None


def test_parse():
    test = (3, 2, 3, None, 3, None, 1)
    assert repr(list_to_binary_tree(test)) == \
        '<3, <2, None, <3, None, None>>, <3, None, <1, None, None>>>'
    test = ()
    assert repr(list_to_binary_tree(test)) == \
        'None'
    test = (3,)
    assert repr(list_to_binary_tree(test)) == \
        '<3, None, None>'


def test():
    s = solution.Solution()
    tests = (((3, 2, 3, None, 3, None, 1), 7),
             )
    for t, ans in tests:
        t = list_to_binary_tree(t)
        actual = s.rob(t)
        assert actual == ans, 'failed test: input = {}; expected = {}; actual = {}'.format(t, ans, actual)
