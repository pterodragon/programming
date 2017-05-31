module Main where

import Combination

run f = do
    let x = f [1,3,2,1] 3
    print x
    let y = f [1,2] 1
    print y
    let z = f [1] 2
    print z
    let w = f ([] :: [Int]) 1
    print w


main :: IO ()
main = do
    putStrLn "include and exclude"
    run combinations1
    putStrLn "fix element and recur"
    run combinations2
