import Test.Tasty.HUnit
import Test.Tasty
import CombinationTest

main = defaultMain tests
tests :: TestTree
tests = testGroup "Tests" [combinationTest]
