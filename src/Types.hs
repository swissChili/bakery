module Types where

import Data.Map

data CompilerData = CompilerData { cc :: String
                                 , cxx :: String }

type State = Map String [ String ]

data Targets = Targets { libs :: [ String ]
                       , bins :: [ String ] }
                       deriving ( Show )

type Bakery = [ Ast ]

data ToCompile = ToCompile { state :: State
                           , targets :: Targets }
                           deriving ( Show )

data Ast = Set String [ String ]
         | Push String [ String ]
         | Lib String
         | Bin String
         deriving ( Show )


