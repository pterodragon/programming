from itertools import chain


class Solution(object):

    def islandPerimeter(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        return sum(sum(x != y for x, y in zip(chain([0], row), chain(row, [0])))
                   for row in chain(grid, zip(*grid)))
