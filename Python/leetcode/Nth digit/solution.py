class Solution:
    def findNthDigit(self, n: int) -> int:
        if n < 10:
            return n
        # 9 1-digit numbers
        # 90 2-digit numbers
        # 900 3-digit numbers
        # ...
        # step 1 find out which level the digit it belongs to
        a = n
        i = 0
        while a > 0:
            c = (9 * 10 ** i) * (i + 1)
            i += 1
            if a - c < 0:
                break
            a -= c
        # n'th digit count is within the i-digit numbers
        # a is how many digits pass the i-digit numbers

        # step 2 locate the exact number
        s = (a - 1) // i
        d = (a - 1) % i  # how many digits pass that number
        # s'th number (0-indexed)
        num = 10 ** (i - 1) + s

        # extract the digit
        e = i - d - 1  # 10^e'th place
        t = num // (10 ** e)
        return t % 10
