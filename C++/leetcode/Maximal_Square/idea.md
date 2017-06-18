### Given
    bool m[H][W]

### States of problem
    lc[r][s] = side of largest square of "1" from using just m[p][q] where p <= r, q <= s; must include m[r][s] else this equals to 0

### Answer
    max(lc[r][s])

### Recursion
    lc[r][0] = m[r][0] for r in [0, H - 1]
    lc[0][s] = m[0][s] for r in [0, W - 1]
    lc[r][s] = m[r][s] ? 1 + min(lc[r - 1][s - 1], lc[r - 1][s], lc[r][s - 1]) : 0

     oox
    ooox
    ooox
    xxx?

### Help

