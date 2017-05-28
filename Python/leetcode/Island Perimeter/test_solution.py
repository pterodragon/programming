import nose
import solution


def test_solution():
    t1 = [[0, 1, 0, 0], [1, 1, 1, 0], [0, 1, 0, 0], [1, 1, 0, 0]]
    result = solution.Solution().islandPerimeter(t1)
    expected = 16
    assert result == expected
