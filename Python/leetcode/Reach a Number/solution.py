def isqrt(n):
    x = n
    y = (x + 1) // 2
    while y < x:
        x = y
        y = (x + n // x) // 2
    return x


class Solution:
    def reachNumber(self, target: int) -> int:
        # (x(x+1))/2 >= n
        # x^2+x-2n >= 0
        # x = 1/2*(-1+sqrt(1^2-4(1)(-2n)))
        # x = 1/2*(-1+sqrt(1+8n))
        n = abs(target)
        a = isqrt(1 + 8*n)
        is_square = a * a == (1 + 8 * n)
        x = (-1 + a) // 2
        if is_square:
            return x
        for _ in range(3):
            x += 1
            sum_is_odd = (x % 4) in (1, 2)
            difference_is_even = (sum_is_odd == (n % 2 == 1))
            if difference_is_even:
                return x
    # 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66, 78,
    # o  o  e  e   o   o   e   e  o    o
    # n(n+1)/2 is is even for n = 4x-1 or 4x for all x in Z
    # (4x-1)(4x)/2 -> even
    # 4x(4x+1) -> even
    # n(n+1)/2 is is odd for n = 4x-3 or 4x-2 for all x in Z
    # (4x-3)(4x-2)/2 = (4x-3)(2x-1) -> odd
    # (4x-2)(4x-1)/2 = (2x-1)(4x-1) -> odd
