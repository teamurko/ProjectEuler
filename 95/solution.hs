module Main where
import qualified Data.Set as Set
import qualified Data.Map as Map
import qualified Data.List as List

divisorsSumImpl :: Integral a => a -> a -> a
divisorsSumImpl 1 1 = 0
divisorsSumImpl n 1 = 1 + (divisorsSumImpl n 2)
divisorsSumImpl n d = if d * d > n then 0 else
                      if d * d == n then d else
                      if n `mod` d == 0 then d + (n `div` d) + next else
                      next where next = divisorsSumImpl n (d + 1)

divisorsSum :: Integral a => a -> a
divisorsSum 1 = 0
divisorsSum n = divisorsSumImpl n 1

maxNumber :: Integral a => a
maxNumber = 10000

isInRange :: Integral a => a -> Bool
isInRange x = (x >= 1) && (x <= maxNumber)

amicableSearch element globalUsed localUsed step =
                    if not (isInRange element) then ((0, -1), localUsed) else
                    if Set.member element globalUsed then ((0, -1), localUsed) else
                    if Map.member element localUsed then ((step - (localUsed Map.! element), element), localUsed) else
                    amicableSearch (divisorsSum element) globalUsed updatedLocalUsed (step + 1)
                    where leaveNewest = \key new old -> new
                          updatedLocalUsed = Map.insertWithKey leaveNewest element step localUsed

calc element globalUsed best =
                    if not (isInRange element) then best else
                    if Set.member element globalUsed then next else
                    calc (element + 1) (Set.union globalUsed localUsed) bestOfTwo
                    where next = calc (element + 1) globalUsed best
                          tryResult = amicableSearch element globalUsed (Map.fromList []) 0
                          candidate = fst tryResult
                          localUsed = Set.fromList (Map.keys (snd tryResult))
                          bestOfTwo = if fst candidate > fst best then candidate else best

generateChain :: Integral a => a -> [a] -> [a]
generateChain n used = if not (null used) && n == head used then used else
                       generateChain (divisorsSum n) (used ++ [n])

main = do
    let bestTuple = calc 1 (Set.fromList []) (0, -1)
    let chain = generateChain (snd bestTuple) []
    print $ minimum chain

--compile with -rtsopts to switch on runtime options
--run with stacksize option ./solution -K256000000
