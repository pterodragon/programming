a =     [2, 6, 4, 8, 10, 9, 15]

If sorting a subarray starting from this index (assuming the elements prior to this index is sorted), the minimum element has to be >= what
l_min = [-, 2, 6, 6, 8, 10, 10]

Defined similarly:
If sorting a subarray ending at this index (assuming the elements after this index is sorted), the maximum element has to be <= what

r_max = [4, 4, 8, 9, 9, 15, -]

iterate through a_i, 
        
a =             [2, 6, 4, 8, 10, 9, 15]
min_so_far =    [2, 4, 4, 8, 9, 9, 15] // from the right
                    ^
                    first mismatch

a =             [2, 6, 4, 8, 10, 9, 15]
max_so_far =    [2, 6, 6, 8, 10, 10, 15] // from the left
                                 ^
                                 first mismatch
