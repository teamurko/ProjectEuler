module Main where
import qualified Data.List as List

sortedDigits = "123456789"

fibsCut :: (Integer -> Integer) -> Integer -> Integer -> Integer -> [(Integer, Integer)]
fibsCut cut a b id = (id, a) : (fibsCut cut b c (id + 1))
                     where c = cut (a + b)

fibsModulo :: Integer -> [(Integer, Integer)]
fibsModulo n = fibsCut (\x -> mod x n) 1 1 1

fibsPan9DigitalLow = filter isPan9DigitalLow fibs
        where fibs = fibsModulo 1000000000
              isPan9DigitalLow (_, v) = List.sort (show v) == sortedDigits

isPan9DigitalHigh :: Integer -> Bool
isPan9DigitalHigh number = List.sort (take 9 (show number)) == sortedDigits

data Vector2 = Vector2 Integer Integer deriving (Eq, Show)
data Matrix22 = Matrix22 Vector2 Vector2 deriving (Eq, Show)

innerProduct (Vector2 a1 a2) (Vector2 b1 b2) = a1 * b1 + a2 * b2

element :: Vector2 -> Integer -> [Integer]
element (Vector2 a _) 0 = [a]
element (Vector2 _ a) 1 = [a]
element _ _ = []

row :: Matrix22 -> Integer -> [Vector2]
row (Matrix22 v1 _) 0 = [v1]
row (Matrix22 _ v2) 1 = [v2]
row _ _ = []

column :: Matrix22 -> Integer -> [Vector2]
column (Matrix22 (Vector2 a1 _) (Vector2 a2 _)) 0 = [Vector2 a1 a2]
column (Matrix22 (Vector2 _ a1) (Vector2 _ a2)) 1 = [Vector2 a1 a2]
column _ _ = []

mul :: Matrix22 -> Matrix22 -> Matrix22
mul m1 m2 = Matrix22 (Vector2 (innerProduct r1 c1) (innerProduct r1 c2))
                     (Vector2 (innerProduct r2 c1) (innerProduct r2 c2))
            where
                r1 = head (row m1 0)
                r2 = head (row m1 1)
                c1 = head (column m2 0)
                c2 = head (column m2 1)

fastPow :: (a -> a -> a) -> a -> Integer -> a -> a
fastPow _ _ 0 result = result
fastPow mul multiplier index result =
                fastPow mul multiplier2 (div index 2) result2
            where
                result2 = if mod index 2 == 1 then mul result multiplier
                          else result
                multiplier2 = mul multiplier multiplier

fibByIndex :: Integer -> Integer
fibByIndex index =
                head (element (head (row poweredMatrix 0)) 1)
            where
                unityMatrix = Matrix22 (Vector2 1 0) (Vector2 0 1)
                fibMatrix = Matrix22 (Vector2 1 1) (Vector2 1 0)
                poweredMatrix = fastPow mul fibMatrix index unityMatrix

main = do
    let fibs = take 112 fibsPan9DigitalLow
    let answer = filter (\(id, _) -> isPan9DigitalHigh (fibByIndex id)) fibs
    print $ answer

--compile with -rtsopts to switch on runtime options
--run with stacksize option ./solution -K256000000
