module Main where

numSubRectangles :: Integral a => a -> a -> a
numSubRectangles dimOne dimTwo = div ((dimOne + 1) * (dimTwo + 1) * dimOne * dimTwo) 4

list :: Integral a => a -> [a]
list n = if n < 1 then [] else (list (n - 1)) ++ [n]

candidates :: Integral a => [(a, a)]
candidates = [(x * y, abs((numSubRectangles x y) - 2000000)) | x <- (list 100), y <- (list 100)]

closest :: Integral a => [(a, a)] -> (a, a) -> (a, a)
closest lst tupleRes = if lst == [] then tupleRes else if snd (head lst) < snd tupleRes then closest (tail lst) (head lst) else closest (tail lst) tupleRes

initPair :: Integral a => (a, a)
initPair = (-1, 2000000)

main = do
    let ans = (closest candidates initPair)
    putStrLn (show ans)
