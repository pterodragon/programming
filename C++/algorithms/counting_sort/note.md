# Counting sort

`T = "bcacbc"`

```
p: a b c
   1 2 3
```

## Way of doing the partial sums

### First element is `p[0]`

```cpp
partial_sum(begin(p), end(p), begin(p))
```

```
p: a b c
   1 3 6
```

`p[x]` = number of chars smaller than equal to this char `'x'`,
e.g. `p['b'] = 3`: There are 3 chars smaller than or equal to `'b'`
--> just put a `'b'` into `res[3 - 1]` <due to 0 index> and decrement `p['b']`
--> `res[--p['b']] = 'b'`

for stable sort, scan `T` from right to left,
this way the right most `'b'` in `T` is put into the right most `'b'` position first in `res`

### First element is 0

```cpp
  for (int q = 0, sum = 0; q < S; ++q) {
    int t = p[q];
    p[q] = sum;
    sum += t;
  }
```

```
p2: a b c | ? // column ? is not needed in real code
    0 1 3 | 6
```
`p2[x]`: position char `'x'` should start in `res` (also equal to number of char strictly less than char `'x'` before this position),
e.g. `p['b'] = 1`: `'b'` should start from pos `1`
--> just put a `'b'` into `res[1]` then increment `p['b']`
--> `res[p['b']++] = 'b'`

for stable sort, scan `T` from left to right
this way the left most `'b'` in `T` is put into the left most `'b'` position first in `res`
