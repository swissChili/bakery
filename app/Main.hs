module Main where

import Lib
import System.IO
import Interpreter
import Make


main :: IO ()
main = do
  bakery <- readFile "bakery"
  case parseBakery bakery of
    Right a -> putStrLn $ make $ interpretStart a
    Left a -> print a
