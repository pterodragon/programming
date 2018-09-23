class Solution:
    def partition(self, s):
        """
        :type s: str
        :rtype: List[List[str]]
        """
        """
        sample strings
        'abcdedcbabc'
        'ababababa'
        'aaaaaaaaa' -> 2^(n-1) ways
        """
        """
        Note:
            how to check if each substring is a palindrome

        ### Idea 1:
        'aaaaaaaaa'
        mp = [1,2,3,4,5,6,7,8,9]  # maximum length of a palindrome
                                    ending with index x

        ### Idea 3:
        O(n^2)
        pp = [[1], [1,2], [1,2,3]]  # possible lengths of palindrome
                                    ending with index x
        ### Idea 4:
        O(n^2)
        is_pal[a][b]
        := s[a:b] is a palindrome

        -> all permutation with is_pal constraint
        """

        n = len(s)
        is_pal = [[1] * (n+1) for _ in range(n)]
        for a in range(2, n + 1):  # length of substring
            for i in range(n - a + 1):  # start index
                is_pal[i][i + a] = \
                    is_pal[i + 1][i + a - 1] * (s[i] == s[i + a - 1])

        def perm(s, a, b):
            ans = []
            if is_pal[a][b]:
                ans.append([s[a:b]])
            for e in range(a + 1, b):
                if is_pal[a][e]:
                    for p in perm(s, e, b):
                        ans.append([s[a:e], *p])
            return ans

        return perm(s, 0, n)
