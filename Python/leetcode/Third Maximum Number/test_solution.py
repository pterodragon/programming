from solution import Solution as S


def test():
    assert S().thirdMax([3, 2, 1]) == 1
    assert S().thirdMax([1, 2]) == 2
    assert S().thirdMax([2, 2, 3, 1]) == 1
