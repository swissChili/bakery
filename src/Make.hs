module Make where

import Types
import qualified Data.Map as Map
import Data.List

getCompilerData :: () -> CompilerData
getCompilerData () = CompilerData "cc" "c++"

sources x = "$(" ++ x ++ ".sources)"
headers x = "$(" ++ x ++ ".headers)"

makeLibs :: [String] -> String -> String
makeLibs [] c = c
makeLibs (x:xs) a = a ++ x ++ ": " ++ sx ++ hx ++ "\n" ++ r
  where r = "\t$(CXXC) -o " ++ x ++ " " ++ sx ++ "\n\n"
        sx = sources x
        hx = headers x

makeBins = makeLibs

makeState :: [(String, [String])] -> String -> String
makeState [] a = a
makeState ((a, b):xs) c = makeState xs r
  where bs = intercalate " " b
        r = c ++ a ++ " = " ++ bs ++ "\n"

makeTargets :: Targets -> String
makeTargets (Targets l b) = makeLibs l "" ++ makeBins b ""

makeClean :: Targets -> String
makeClean (Targets a b) = "clean: " ++ intercalate " " (a ++ b) ++ "\n"

make :: ToCompile -> String
make (ToCompile s t) = ms ++ "\n\n" ++ mt ++ "\n" ++ makeClean t ++ phony
  where ms = makeState (Map.toList s) ""
        mt = makeTargets t
        phony = ".PHONY: clean"

