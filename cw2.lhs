G52AFP Coursework 2 - Monadic Compiler

Wang Jinhao
psyjw19@nottingham.ac.uk

--------------------------------------------------------------------------------

> import Control.Monad.Trans.Writer.Lazy
> import Control.Monad.Trans

Imperative language:

> data Prog = Assign Name Expr
>           | If Expr Prog Prog
>           | While Expr Prog
>           | Seqn [Prog]
>             deriving Show
>
> data Expr = Val Int | Var Name | App Op Expr Expr
>             deriving Show
>
> type Name = Char
>
> data Op   = Add | Sub | Mul | Div
>             deriving Show

Factorial example:

> fac :: Int -> Prog
> fac n = Seqn [Assign 'A' (Val 1),
>               Assign 'B' (Val n),
>               While (Var 'B') (Seqn
>                  [Assign 'A' (App Mul (Var 'A') (Var 'B')),
>                   Assign 'B' (App Sub (Var 'B') (Val (1)))])]

If statement example:

> eq :: Int -> Int -> Prog
> eq a b = Seqn [Assign 'A' (Val a),
>                Assign 'B' (Val b),
>                If (App Sub (Var 'A') (Var 'B')) (Seqn [Assign 'A' (App Add (Var 'A') (Val (3)))]) (Seqn [Assign 'A' (App Sub (Var 'A') (Val (3)))])]

Virtual machine:

> type Stack = [Int]
>
> type Mem   = [(Name,Int)]
>
> type Code  = [Inst]
> 
> data Inst  = PUSH Int
>            | PUSHV Name
>            | POP Name
>            | DO Op
>            | JUMP Label
>            | JUMPZ Label
>            | LABEL Label
>              deriving Show
> 
> type Label = Int

State monad:

> type State = Label
>
> newtype ST a = S (State -> (a, State))
>
> app :: ST a -> State -> (a,State)
> app (S st) x 	=  st x
>
> instance Functor ST where
>    -- fmap :: (a -> b) -> ST a -> ST b
>    fmap g st = S (\s -> let (x,s') = app st s in (g x, s'))
>
> instance Applicative ST where
>    -- pure :: a -> ST a
>    pure x = S (\s -> (x,s))
>
>    -- (<*>) :: ST (a -> b) -> ST a -> ST b
>    stf <*> stx = S (\s ->
>       let (f,s')  = app stf s
>           (x,s'') = app stx s' in (f x, s''))
>
> instance Monad ST where
>    -- return :: a -> ST a
>    return x = S (\s -> (x,s))
>
>    -- (>>=) :: ST a -> (a -> ST b) -> ST b
>    st >>= f = S (\s -> let (x,s') = app st s in app (f x) s')

Exercise 1-----------------------------------------------------------------------------------------
Define a state transformer which returns the current state as the label, and the next integer as the new state

> increase :: ST Label
> increase = S (\n -> (n, n+1))

Function evalExpr takes an Expr as an argument and returns an Inst in a list form

> evalExpr :: Expr -> Code
> evalExpr (Val n) = [PUSH n]
> evalExpr (Var name) = [PUSHV name]
> evalExpr (App operation exprone exprtwo) = (evalExpr exprone) ++ (evalExpr exprtwo) ++ [(DO operation)]

ST [Inst] stands for "Label -> ([Inst], Label)". Here the value of Label is recorded by the state monad
Function evalProg takes a Prog as an argument, and returns a Code monad using state transformer and do notation 

> evalProg :: Prog -> ST Code
> evalProg (Assign name expr) = do return ((evalExpr expr) ++ [POP name])
> evalProg (If expr progone progtwo) = do a <- increase
>                                         b <- increase
>                                         prog' <- evalProg progone
>                                         prog'' <- evalProg progtwo
>                                         return ((evalExpr expr) ++ [JUMPZ a] ++ prog' ++ [JUMP b] ++ [LABEL a] ++ prog'' ++ [LABEL b])
> evalProg (While expr prog) = do a <- increase
>                                 b <- increase
>                                 prog' <- evalProg prog
>                                 return ([LABEL a] ++ (evalExpr expr) ++  [JUMPZ b] ++ prog' ++  [JUMP a] ++ [LABEL b])
> evalProg (Seqn progs) | (length progs) == 0   = do return []
>                       | otherwise             = do prog' <- evalProg (head progs)
>                                                    progs' <- evalProg (Seqn (tail progs))
>                                                    return (prog' ++ progs') 

Function comp takes the result of function evalProg and applies function app which takes the initial state as an argument to the reult to produce a Code
The actual return type of app is a tuple: (Code, the current state). So need to apply function fst to fetch out the first element

> comp :: Prog -> Code
> comp prog = fst (app (evalProg prog) 0)

Exercise 2-----------------------------------------------------------------------------------------
Function find is used to locate the place in Code where JUMP and JUMPZ want to go to
It takes an Int which is provided by JUMP or JUMPZ and a list Inst to find the appointed LABEL to jump to

> find :: Int -> Code -> Code
> find target (LABEL l : codes) | target == l   = codes
>                               | otherwise     = find target codes
> find target (_:codes) = find target codes

Function manipulate is used to maniulate the memory list.
It takes variable name and a value and stores them as a tuple in the memory list

> manipulate :: Name -> Int -> Mem -> Mem
> manipulate name stack [] = [(name, stack)]
> manipulate name stack (mem:mems) | name == fst mem  = (name, stack):mems
>                                  | otherwise        = mem : (manipulate name stack mems)

Function evalOp is used to transform Op into corresponding computation

> evalOp :: Int -> Int -> Op -> Int
> evalOp a b Add = a + b
> evalOp a b Sub = b - a
> evalOp a b Mul = a * b
> evalOp a b Div = b `div` a

Function evalInst takes a Code and performs corresponding operation on memory list and stack list
It takes 2 Code type values. They are the same. The first value is never changed. It is used for Function find to locate the appointed location required by JUMP or JUMPZ

> evalInst :: [Inst] -> [Inst] -> Mem -> Stack -> Mem
> evalInst store [] memory stack = memory
> evalInst store (PUSH n : code) memory stack = evalInst store code memory (n:stack)
> evalInst store (PUSHV name : code) (mem:mems) stack | name == fst mem    = evalInst store code (mem:mems) ((snd mem):stack)
>                                                     | otherwise          = evalInst store (PUSHV name : code) (mems ++ [mem]) stack
> evalInst store (POP name : code) memory (stack:stacks) = evalInst store code (manipulate name stack memory) stacks
> evalInst store (DO operation : code) memory (stackone:stacktwo:stacks) = evalInst store code memory ((evalOp stackone stacktwo operation):stacks)
> evalInst store (JUMP target : code) memory stack = evalInst store (find target store) memory stack
> evalInst store (JUMPZ target : code) memory (stack:stacks) | stack == 0   = evalInst store (find target store) memory stacks
>                                                            | otherwise    = evalInst store code memory stacks
> evalInst store (LABEL target : code) memory stack = evalInst store code memory stack

Function exec takes a code and returns the finish state of the memory list

> exec :: Code -> Mem
> exec code = evalInst code code [] []

Bonus----------------------------------------------------------------------------------------------
Function evalProgW is the same as the function evalProg. 
The only difference is that the return type is wrapped with a WriterT transformer

> evalProgW :: Prog -> WriterT Code ST ()
> evalProgW (Assign name expr) = tell ((evalExpr expr) ++ [POP name])
> evalProgW (If expr progone progtwo) = do a <- lift increase
>                                          b <- lift increase
>                                          tell ((evalExpr expr) ++ [JUMPZ a])
>                                          evalProgW progone
>                                          tell ([JUMP b] ++ [LABEL a])
>                                          evalProgW progtwo
>                                          tell [LABEL b]
> evalProgW (While expr prog) = do a <- lift increase
>                                  b <- lift increase
>                                  tell ([LABEL a] ++ (evalExpr expr) ++  [JUMPZ b])
>                                  evalProgW prog
>                                  tell ([JUMP a] ++ [LABEL b])
> evalProgW (Seqn progs) | (length progs) == 0   = do tell []
>                        | otherwise             = do evalProgW (head progs)
>                                                     evalProgW (Seqn (tail progs))

Function compW is the same as the function comp. 
The only difference is that applying a function execWriterT to unwrap the WriterT transformer 

> compW :: Prog -> Code
> compW prog = fst (app (execWriterT (evalProgW prog)) 0)