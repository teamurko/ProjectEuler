module Main where

maxCoord = 50
data Point = Pt Int Int
ptx (Pt x _) = x
pty (Pt _ y) = y

data Triangle = Tri Point Point
ptf (Tri f _) = f
pts (Tri _ s) = s

sub a b = Pt (ptx a - ptx b) (pty a - pty b)
scalProd a b = (ptx a * ptx b) + (pty a * pty b)
vectProd a b = (ptx a * pty b) - (pty a * ptx b)

isDegenerate t = vectProd (ptf t) (pts t) == 0
isRectangle t = (scalProd (ptf t) (pts t) == 0) || (scalProd (ptf t) (sub (pts t) (ptf t)) == 0) || (scalProd (pts t) (sub (pts t) (ptf t)) == 0)

points = [Pt x y | x <- [0..maxCoord], y <- [0..maxCoord]]
triangles = filter isRectangle (filter (not . isDegenerate) [Tri f s | f <- points, s <- points])

instance (Show Point) where
    show (Pt a b) = "(" ++ show a ++ ", " ++ show b ++ ")"

instance (Show Triangle) where
    show (Tri f s) = "<" ++ show f ++ ", " ++ show s ++ ">"

main = do
    print $ div (length triangles) 2



