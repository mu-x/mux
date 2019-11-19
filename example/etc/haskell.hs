maxOf :: Ord any => [any] -> any
maxOf [x] = x
maxOf (x:tail)
    | x > maxOfTail = x
    | otherwise = maxOfTail
    where maxOfTail = maxOf(tail)


data List any = Nil | Cons any (List any) deriving Show

list :: [any] -> List any
list [] = Nil
list (item:tail) = Cons item (list tail)

join :: List any -> List any -> List any
join Nil item = item
join (Cons item tail) other = Cons item (join tail other)

push :: List any -> any -> List any
push list item = join list (Cons item Nil)

fromList :: List any -> [any]
fromList Nil = []
fromList (Cons item tail) = (item:(fromList tail))
