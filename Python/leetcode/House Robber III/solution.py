class TreeNode(object):

    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

    def __repr__(self):
        return '<{}, {}, {}>'.format(self.val, self.left, self.right)


class Solution(object):

    def rob(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        def f(node):
            if node is None:
                return 0, 0  # prev_rob, prev_no_rob
            la, lb = f(node.left)
            ra, rb = f(node.right)
            return lb + rb, max(lb + rb, la + ra + node.val)
        return max(f(root))
