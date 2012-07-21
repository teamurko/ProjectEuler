module Main where
import Data.Maybe
import qualified Data.Set as Set
import qualified Data.Map as Map
import qualified Data.List as List

eps :: (RealFrac a) => a
eps = 0.00001

digits :: (Enum a, Num a) => [a]
digits = [0..9]

isUnique :: (Eq a, Ord a)  => [a] -> Bool
isUnique [] = True
isUnique (x:xs) = all (/= x) xs && isUnique xs

quadruples = filter isUnique (sequence (List.replicate 4 digits))

tryOperation x y op = if op == '/' then if y == 0 then Nothing else Just (x / y) else
                      if op == '*' then Just (x * y) else
                      if op == '+' then Just (x + y) else
                      if op == '-' then Just (x - y) else Nothing

isInt :: (RealFrac a) => a -> Bool
isInt x = abs (x - fromInteger (round x)) < eps

applyOnce [] = []
applyOnce [x] = []
applyOnce (x:ys) = if null ys then [[x]] else [[e] ++ (tail ys) | e <- (map fromJust (filter isJust [tryOperation x (head ys) op | op <- "*/+-"]))] ++ [[x] ++ e | e <- (applyOnce ys)]

eval [] = []
eval numbers = if (length numbers) == 1 then numbers else
               filter (\x->(x > 0) && (isInt x)) (List.concat (map eval var))
               where var = applyOnce numbers

mex set = head (filter (\x -> not (Set.member x set)) [1..])
toInts [] = []
toInts (x:ys) = (round x) : (toInts ys)

solve [] = Map.fromList []
solve (x:ys) = Map.insert (toInts (List.sort x)) (Set.union (Map.findWithDefault (Set.fromList []) (toInts(List.sort x)) dict) (Set.fromList (map round (eval x)))) dict where dict = solve ys

main = do
    let ans = map (\x -> (mex (snd x), fst x)) (Map.toList (solve quadruples))
    print $ Map.findMax (Map.fromList ans)
