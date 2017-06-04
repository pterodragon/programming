module CombinationTest where

import Combination

import Test.Tasty.HUnit
import Test.Tasty

combs = [
            ("repeat 1", [1,3,2,1], 3, [[1,1,2],[1,1,3],[1,2,3]]),
            ("1 choose 2", [1], 2, []),
            ("1 choose 1", [1], 1, [[1]]),
            ("0 choose 1", [], 1, []),
            ("all same", [1,1,1,1], 3, [[1,1,1]])
        ]

combTests = [
                ("combination1", combination1),
                ("combination2", combination2)
            ]

combinationTest = testGroup "Combination tests" 
    [testGroup testGroupDesc 
        [ testCase description $ f arg1 arg2 @?= expected | (description, arg1, arg2, expected) <- combs] | 
            (testGroupDesc, f) <- combTests]
