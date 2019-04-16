from solution import Solution


def test():
    assert Solution().buddyStrings('aa', 'aa')
    assert Solution().buddyStrings('ab', 'ba')
    assert not Solution().buddyStrings('ab', 'ab')
    assert Solution().buddyStrings('aaabc', 'aaacb')
