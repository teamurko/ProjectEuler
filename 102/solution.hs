module Main where

data Point = Point Int Int

instance Show Point where
    show (Point x y) = "(" ++ show x ++ "," ++ show y ++ ")"

xcoord (Point x _) = x
ycoord (Point _ y) = y

circle :: [Point] -> [Point]
circle points = points ++ [head points]

vectorProduct :: Point -> Point -> Int
vectorProduct first second  =
        (xcoord first) * (ycoord second) - (xcoord second) * (ycoord first)

square :: (Point -> Point -> Int) -> [Point] -> Int
square product [] = 0
square product [point] = 0
square product [ein, zwei] = product ein zwei
square product (x:xs) = (product x (head xs)) + (square product xs)

applyConsequtivePairs :: (a -> a -> b) -> [a] -> [b]
applyConsequtivePairs _ [] = []
applyConsequtivePairs _ [a] = []
applyConsequtivePairs f (x:xs) =
            (f x (head xs)) : (applyConsequtivePairs f xs)

square2 :: (Point -> Point -> Int) -> [Point] -> Int
square2 product xs = (absolute . sum) (applyConsequtivePairs product xs)

absolute :: Int -> Int
absolute x = if x > 0 then x else -x

doesCoverOrigin :: [Point] -> Bool
doesCoverOrigin points =
    (square2 vectorProduct pts) == (square2 positiveVectorProduct pts) &&
    all (\x -> x /= 0) (applyConsequtivePairs vectorProduct pts)
    where positiveVectorProduct = \x y -> absolute (vectorProduct x y)
          pts = circle points

replace :: Char -> Char -> String -> String
replace what by whereString =
    map (\c -> if c == what then by else c) whereString

pointsFromList :: [Int] -> [Point]
pointsFromList [] = []
pointsFromList (x:xs) = (Point x (head xs)) : (pointsFromList (tail xs))

parseInts :: [String] -> [Int]
parseInts [] = []
parseInts (x:xs) = (read x :: Int) : (parseInts xs)

pointsFromString = pointsFromList . parseInts . words

main = do
    input <- getContents
    let triangles = map (\line -> pointsFromString (replace ',' ' ' line)) (lines input)
    print $ length (filter doesCoverOrigin triangles)

--compile with -rtsopts to switch on runtime options
--run with stacksize option ./solution -K256000000
