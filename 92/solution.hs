module Main where

sqr x = x * x
digitSquaresSum n = if n < 10 then sqr n else (sqr (mod n 10)) + digitSquaresSum (div n 10)

ein = 1
neunundachtzig = 89

end n = if n == ein then ein else if n == neunundachtzig then neunundachtzig else end (digitSquaresSum n)

--instance (Show Point) where
--    show (Pt a b) = "(" ++ show a ++ ", " ++ show b ++ ")"

ans = filter (\n-> (end n) == neunundachtzig) [1..10000000]

main = do
    print $ length ans



