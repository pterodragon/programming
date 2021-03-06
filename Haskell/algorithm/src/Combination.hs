-- reference (Japanese) http://www.geocities.jp/m_hiroi/func/haskell06.html
-- http://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/
-- https://wiki.haskell.org/99_questions/Solutions/26
module Combination
    ( combination1,
      combination2
    ) where

import Data.List
import Data.Function

-- include and exclude every elements
combination1 :: Ord a => [a] -> Int -> [[a]]
combination1 xs n = comb n (sort xs) [] [] where
    comb 0 _      ys zs = reverse ys : zs
    comb _ []     _  zs = zs
    comb n (x:xs) ys zs = comb (n - 1) xs (x:ys) (comb n (dropWhile (== x) xs) ys zs)

-- fix element and recur
combination2 :: Ord a => [a] -> Int -> [[a]]
combination2 xs n = comb (sort xs) n where
    comb _ 0  = [ [] ]
    comb xs n = [ y:ys | y:xs' <- fmap head (groupBy ((==) `on` head) (init . tails $ xs)) ++ [], ys <- combination2 xs' (n-1) ]
