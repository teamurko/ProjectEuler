module Main where

isSquare :: Integral a => a -> Bool
isSquare x = (truncate (sqrt (fromIntegral x)))^2 == x

walk n = length (filter (\id -> id) [isSquare (n * n + (x + y) * (x + y)) | x <- (take n [1..]), y <- (take x [1..])])

walked = [walk n | n <- [1..]]

isIntegralLength a b c = if a < b then isIntegralLength b a c else if a < c then isIntegralLength c a b else if b < c then isIntegralLength a c b else isSquare (a * a + (b + c) * (b + c))

countIntegral n = length (filter (\id -> id) [((isIntegralLength a b c) && (a >= b) && (b >= c)) | a <- (take n [1..]), b <- (take n [1..]), c <- (take n [1..])])

target = 1000000
accumulateFirst (x:y) sum n = if sum >= target then n else accumulateFirst y (sum + x) (n + 1)

main = do
    print $ accumulateFirst walked 0 0
