class TreeNode(object):

    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

    def __repr__(self):
        return '<{}, {}, {}>'.format(self.val, self.left, self.right)


class Memoize(object):

    def __init__(self, f):
        self.f = f
        self.memo = {}

    def __call__(self, *args):
        if args not in self.memo:
            self.memo[args] = self.f(*args)
        return self.memo[args]


class Solution(object):

    def rob(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        @Memoize
        def f(node, prev_rob):
            if node is None:
                return 0
            no_rob_curr = f(node.left, False) + f(node.right, False)
            if prev_rob:
                return no_rob_curr
            else:
                return max(no_rob_curr,
                           f(node.left, True) + f(node.right, True) + node.val)
        return max(f(root, False), f(root, True))
