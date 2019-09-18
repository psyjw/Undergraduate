G52AFP Coursework 1 - Connect 4
   
Wang Jinhao
psyjw19@nottingham.ac.uk

----------------------------------------------------------------------

For flexibility, we define constants for the row and column size of the
board, length of a winning sequence, and search depth for the game tree:

> import Data.List
> import Data.Char
> import System.IO
> import System.Random

> rows :: Int
> rows = 6
>
> cols :: Int
> cols = 7
>
> win :: Int
> win = 4
>
> depth :: Int
> depth = 6

The board itself is represented as a list of rows, where each row is
a list of player values, subject to the above row and column sizes:

> type Board = [Row]
>
> type Row = [Player]

In turn, a player value is either a nought, a blank, or a cross, with
a blank representing a position on the board that is not yet occupied:

> data Player = O | B | X
>               deriving (Ord, Eq, Show)

The following code displays a board on the screen:

> showBoard :: Board -> IO ()
> showBoard b = putStrLn (unlines (map showRow b ++ [line] ++ [nums]))
>               where
>                  showRow = map showPlayer
>                  line    = replicate cols '-'
>                  nums    = take cols ['0'..]
>
> showPlayer :: Player -> Char
> showPlayer O = 'O'
> showPlayer B = '.'
> showPlayer X = 'X'

The function empty is used to initiate an empty board with appointed number of rows and columns

> empty :: Board
> empty = replicate rows (replicate cols B)

The function next is used to switch between computer and user

> nextPlayer :: Player -> Player
> nextPlayer O = X
> nextPlayer X = O

The function diags is used to fetch the diagonal starting from the left above vertex

> diags :: Board -> Int -> [Player]
> diags b num = [b !! r !! r | r <- [0..num-1]]

The function getRowDiag calls function diags to fetch the diagonal, then eliminate the first row of the current board, and then calls diags again to fetch the new diagonal.
Repeat until the length of the diagonal is smaller than 4.

> getRowDiag :: Board -> Int -> [Row]
> getRowDiag _ 3 = []
> getRowDiag b r = [diags b r] ++ getRowDiag (tail b) (r-1)

The function getColDiag calls function diags to fetch the diagonal, then eliminate the first column of the current board, and then calls diags again to fetch the new diagonal.
Repeat until the length of the diagonal is smaller than 4.

> getColDiag :: Board -> Int -> [Row]
> getColDiag _ 3 = []
> getColDiag b r = [diags b r] ++ getColDiag (transpose(tail (transpose b))) (r-1)

The function getDiags calls function getRowDiag and getColDiag to fetch all diagonals (which are from top left to bottom right) in the board whose length are equal or larger than 4.
For diagonals who are from top right to bottom left, just apply the library function reverse to the board, to reverse these diagonals to be from top left to bottom right.

> getDiags :: Board -> Int -> [Row]
> getDiags b r = getRowDiag b r ++ getColDiag (transpose(tail(transpose b))) r

The function countNum is used to count the number of the required pieces

> countNum :: Player -> Board -> Int
> countNum p b = length (filter (==p) (concat b))

The funtion turn calls funtion countNum to decide who is the next to play, Player X or Player O

> turn :: Board -> Player
> turn b = if numO > numX then X else O
>          where 
>			numO = countNum O b
>			numX = countNum X b

The funtion hasRow is used to check whether there are 4 same consecutive pieces in one line

> hasRow :: Player -> Row -> Bool
> hasRow p r | (length r) < 4						= False
>			 | (length (takeWhile (==p) r)) == 4	= True
>			 | otherwise							= hasRow p (tail r)

The funtion hasWon calls function hasRow to check whether there are 4 same consecutive pieces in any rows, columns or diagonals

> hasWon :: Player -> Board -> Bool
> hasWon p b = any wins row || any wins col || any wins diag
>			   where
>               wins = hasRow p
>               row = b
>               col = transpose b
>               diag = (getDiags b rows) ++ (getDiags (map reverse b) rows)

The funtion hasFull is used to checkout whether there is no blank space on the board

> hasFull :: Board -> Bool
> hasFull b = if any (==B) (concat b) then False else True

The function valid is used to checkout whether the move has gone out of boundary

> valid :: Board -> Int -> Bool
> valid b m = if ((concat b) !! m) == B then True else False

The function insertMove is used to insert the move into the correct place on the board

> insertMove :: Player -> Int -> Row -> Row
> insertMove p m r = if (r !! m) == B then xs ++ [p] ++ ys else insertMove p (m + cols) r
>				 	   where (xs, B : ys) = splitAt m r

The function chop is used to split a list into maximal segments by appointed length

> chop :: Int -> [Player] -> [[Player]]
> chop n [] = []
> chop n xs = take n xs : chop n (drop n xs)

The function move calls function valid to check whether the move has gone out of boundary
If no, calls funtion insertMove to insert the move into the correct place on the board and calls function chop to return a Board type value
If yes, return [] which is an error

> move :: Player -> Int -> Board -> [Board]
> move p m b = if valid b m then [chop cols (reverse(insertMove p (rows - m) (reverse(concat b))))] else []

The function getMove is used to ask the player to enter a move and check whether the move is valid or not
It will only accept input which has one digit number.

> getMove :: IO Int
> getMove = do putStr "Player O, enter your move: "
>              x <- getLine
>              if x /= [] && (length x) == 1 && isDigit (head x) then
>                 do let m = digitToInt (head x)
>                    if m >= 0 && m <= 6 then
>                       return m
>                    else
>                       do putStrLn "Error: Invalid Number!"
>                          getMove
>              else
>                 do putStrLn "Error: Invalid Number!"
>                    getMove

Declare the Tree type which is constituted of a node and a list of subtrees

> data Tree a = Node a [Tree a]
>				deriving (Eq, Show)

The function treeMove is used to return all possible moves for the next step
It will return an empty list if one side has won or the board is full

> treeMove :: Board -> Player -> [Board]
> treeMove b p | hasWon p b = []
>			   | hasFull b  = []
>              | otherwise  = do m <- [0..6]
>                                move p m b

The function gameTree is used to establish the whole tree, starting from the current player.
Root Node is the current board, subtrees are possible moves for the next step of current player.
Then calls itself recursively until the game tree is expanded to the required depth

> gameTree :: Board -> Player -> Int -> Tree Board
> gameTree b p d | d > 0    = Node b [gameTree b' (nextPlayer p) (d-1) | b' <- treeMove b p]
>                | d == 0   = Node b []

The function label is used to evaluate current board and return the value if there is a winner (B means a draw or no one has won in the current situation)

> label :: Board -> Player
> label b | hasWon O b      = O
>         | hasWon X b      = X
>         | otherwise       = B

The funtion minimax is used to return a tree with different boards marked by who will win the game (B means a draw or no one has won in the current situation)

> minimax :: Tree Board -> Tree (Board, Player)
> minimax (Node b ts) | ts == []    = Node (b, label b) []
>                     | otherwise   = if turn b == O then Node (b, minimum ps) ts' else Node (b, maximum ps) ts'
>                                       where ts' = map minimax ts
>                                             ps  = [p | Node (_,p) _ <- ts']

The function bestMove is used to select the best possible move for computer's next step
The best choice is evaluated from the bottom of the game tree whose depth is 6
If there are multiple best moves, computer will choose the first possible move

> bestMove :: Board -> Player -> Board
> bestMove b p = head [b' | Node (b', p') _ <- ts, p' == best]
>                where tree = gameTree b p depth
>                      Node (_,best) ts = minimax tree

The function minimin is used to return all worst moves that computer can make, which means no matter whose turn it is, the game tree will always return the smallest value (which should be O or B)
The aim of this function is to correct some situations that computer won't block an obivous 3 player's pieces.
The reason for these situations is that computer has detected that no matter how it moves, it will lose after 3 rounds, so it makes a meaningless move instead of blocking the obvious one.
Though there is no problem with the game AI, I make this function to let the AI seems more reasonable for every move

> minimini :: Tree Board -> Tree (Board, Player)
> minimini (Node b ts) | ts == []    = Node (b, label b) []
>                      | otherwise   = Node (b, minimum ps) ts'
>                                      where ts' = map minimini ts
>                                            ps  = [p | Node (_,p) _ <- ts']

The function blockMove is used to make the best move depending on a game tree whose depth is only 2.
That means, the computer will block the player's way if the player can win in the next move.

> blockMove :: Board -> Player -> Board
> blockMove b p = head [b' | Node (b', p') _ <- ts, p' == best]
>                 where tree = gameTree b p 2
>                       Node (_,best) ts = minimax tree

The function choiceMove is used to detect whether the player can win in the next move.
If the player can, then block the way directly. Otherwise, expand the normal game tree with depth of 6.

> choiceMove :: Board -> Player -> Board
> choiceMove b p | worst == O     = blockMove b p
>                | otherwise      = bestMove b p
>                                   where tree = gameTree b p 2
>                                         Node (_,worst) ts = minimini tree

The main function creates an empty board and starts game with the user goes first.
hSetBuffering is a library function which used to turn output buffering off, or the display will be wrong.

> main :: IO ()
> main = do hSetBuffering stdout NoBuffering
>           play empty O

The function play is used to display the board and call the function play' to evaluate the win and loss or make the move

> play :: Board -> Player -> IO()
> play b p = do showBoard b
>               play' b p

The function play' is used to evaluate the win and loss to decide whether the game has terminated.
If not, make the move and call the function play recursively.

> play' :: Board -> Player -> IO()
> play' b p
>	| hasWon O b 		  = putStrLn "Player O wins!\n"
>	| hasWon X b 		  = putStrLn "Player X wins!\n"
>	| hasFull b 		  = putStrLn "It is a draw!\n"
>   | p == O              = do m <- getMove
>                              if (move p m b) == [] then
>                                 do putStrLn "Error: Invalid move!"
>                                    play' b p
>                              else
>	                              play (head(move p m b)) (nextPlayer p)
>	| p == X              = do putStrLn "Player X is thinking..."
>	                           play (choiceMove b p) (nextPlayer p)

----------------------------------------------------------------------