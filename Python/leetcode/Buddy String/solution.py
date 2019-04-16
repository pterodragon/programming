class Solution:
    def buddyStrings(self, A: str, B: str) -> bool:
        if len(A) != len(B):
            return False
        swap = 0
        sa, sb = None, None
        for a, b in zip(A, B):
            if a == b:
                continue
            if swap > 1 or (sa and (sa != b or sb != a)):
                return False
            swap += 1
            sa, sb = a, b
        return bool(swap) or (len(set(A)) != len(A))
