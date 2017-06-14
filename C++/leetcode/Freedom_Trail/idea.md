### Given
    ring: max 100 chars; length = lr; lower case letters only
    key:  max 100 chars; length = lk; lower case letters only

### States of problem
    f[a][b] = steps needed to spell key[:a + 1] end position must be at ring[b] (including pressing the button)
    Space Complexity = O(lr * lk) or (O(lk) since it depends on only the previous result)

### Answer
    min(f[lk - 1][x]) where ring[x] == key[lk - 1]

### Recursion
    f[a][b] = min(f[a - 1][x] + dist(x, b)) + 1 where ring[x] == key[a - 1]
    f[0][x] = x + 1 for ring[x] == key[0]; o.w. infinity
    Note: 
        The + 1 is for pushing the center button
        also note that dist(x, b) should take into account the ring nature
        i.e. dist(p, q) = min(abs(q - p), len(ring) - abs(q - p))

### Help
    {char: [list of positions of char]} for the ring
    Try to do the top down approach and sum through (like the C++ solution of "Ones and Zeros") ???
