# Permuted Longest Common Prefix
$$
PLCP[sa[i]] = LCP[i]
$$

## PLCP theorm
$$
PLCP[i] \ge PLCP[i - 1] - 1
$$
meaning PLCP can at most decrease 1 one step at a time

Proof:
Let $sa[x] = 0 \Rightarrow T[sa[x]:] = T[0:] = T$
Let $sa[y] = 1 \Rightarrow T[sa[y]:] = T[1:]$

Since length of $T[sa[x]:]$ is 1 more than $T[sa[y]:]$ and
$PLCP[sa[x]] = PLCP[0] = LCP[x]$ referring to $(sa[x], sa[x - 1]) = (0, ?)$
$PLCP[sa[y]] = PLCP[1] = LCP[y]$ referring to $(sa[y], sa[y - 1]) = (1, ??)$

Let $LCP[x] = q > 1$
$q = 0, 1 \Rightarrow PLCP[0] = 0, 1; PLCP[1] \ge PLCP[1 - 1] - 1 = -1, 0\therefore$ the theorem holds

say
$T[sa[x]:] = T[0:] = T = t_0t_1\dots t_{q - 1}\dots t_n$
$T[sa[x - 1]:] = t_{z}t_{z + 1}\dots t_{z + q - 1}\dots t_n$
where $t_{z}t_{z + 1}\dots t_{z + q - 1} = t_0t_1\dots t_{q - 1}$
and $T[sa[x - 1]:]$ is lexicographically smaller than $T[sa[x]:]$

losing length of 1 starting from index $1$,
$T[sa[y]:] = T[1:] = T = t_1t_2\dots t_{q - 1}\dots t_n$
$T[sa[y - 1]:]$ must have a prefix $t_1t_2\dots t_{q - 1}$ starting from another index
because there is at least one string $W = T[sa[x - 1] + 1:] =t_{z + 1}\dots t_{z + q - 1}$ which spells that prefix and $W$ is lexicographically smaller than $T[sa[y]:]$

same argument applies for $sa[x] = a, sa[y] = a + 1$
