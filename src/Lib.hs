module Lib where

import Text.ParserCombinators.Parsec
import Text.Parsec.Char
import Types

ws = many $ oneOf " \t"
ws1 = many1 $ oneOf " \t"
nl = many1 newline

ident = many1 $ noneOf " \r\n\t"

idents = many1 $ ws >> ident

def :: GenParser Char st Ast
def = do
  name <- ident
  ws
  char '='
  val <- idents
  nl
  return $ Set name val

peq :: GenParser Char st Ast
peq = do
  name <- ident
  ws
  string "+="
  val <- idents
  nl
  return $ Push name val

lib :: GenParser Char st Ast
lib = do
  string "library"
  ws1
  val <- ident
  nl
  return $ Lib val

bin :: GenParser Char st Ast
bin = do
  string "target"
  ws1
  val <- ident
  nl
  return $ Bin val


topLevel = many1 tl
  where tl = try def
          <|>try peq
          <|>try lib
          <|>try bin

parseBakery :: String -> Either ParseError Bakery
parseBakery = parse topLevel "(Bakery)"
