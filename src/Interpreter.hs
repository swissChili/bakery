module Interpreter where

import Types
import qualified Data.Map as Map

interpret :: Targets -> State -> Bakery -> ToCompile
interpret t s [] = ToCompile s t

interpret t s ((Set a b):xs) = interpret t ns xs
  where ns = Map.insert a b s

interpret t s ((Push a b):xs) = interpret t ns xs
  where
    old = case s Map.!? a of
      Nothing -> []
      Just x -> x
    new = old ++ b
    ns = Map.insert a new s


interpret (Targets l b) s ((Lib a):xs) = interpret ts s xs
  where ts = Targets { libs = l ++ [a]
                     , bins = b }

interpret (Targets l b) s ((Bin a):xs) = interpret ts s xs
  where ts = Targets { libs = l
                     , bins = b ++ [a]}


interpretStart = interpret (Targets [] []) Map.empty
