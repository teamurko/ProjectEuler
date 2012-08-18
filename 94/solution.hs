module Main where
import Data.Maybe
import qualified Data.Set as Set
import qualified Data.Map as Map
import qualified Data.List as List
import qualified Data.Bits as Bits

isSquare :: Integral a => a -> Bool
isSquare x = (truncate (sqrt (fromIntegral x)))^2 == x

zweiCount :: Integral a => a -> a
zweiCount x = if (x `mod` 2) == 1 then 0 else 1 + (zweiCount (x `div` 2))

isIntegralSquare :: Integral a => a -> a -> Bool
isIntegralSquare x y = isSquare (4 * x * x - y * y) && ((zweiCount (4 * x * x - y * y)) `div` 2 + (zweiCount y) >= 2)

isAlmostEquilateral :: Integral a => (a, a) -> Bool
isAlmostEquilateral tuple = isIntegralSquare (fst tuple) (snd tuple)

maxPerimeter = 1000 * 1000 * 1000

candidates = concat (map (\y -> [(x, x + y) | x <- takeWhile (\x -> 3 * x + y <= maxPerimeter) [2..]]) [1, -1])

main = do
    let result = sum [2*(fst x) + (snd x) | x <- (filter isAlmostEquilateral candidates)]
    print $ result
