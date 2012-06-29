module Main where
import Data.List

isPrime n = (take 1 [x | x <- [2..], n `mod` x == 0]) == [n]
primes = filter isPrime [2..]

target = 50 * 1000 * 1000
primePows2 = filter (\x -> x < target) (map (^2) (take 10000 primes))
primePows3 = filter (\x -> x < target) (map (^3) (take 1000 primes))
primePows4 = filter (\x -> x < target) (map (^4) (take 100 primes))

main = do
    let two = filter (\x -> x < target) [x + y | x <- primePows2, y <- primePows3]
    print $ filter (\x -> x < target) [x + y | x <- two, y <- primePows4]

