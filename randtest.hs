module Main where

import Data.List
import Data.Word
import Data.ByteString.Builder
import qualified Data.ByteString.Lazy.Char8 as BS
import System.Environment
import System.Random
import Control.Monad.State

type Rand a = State StdGen a

randChar :: Rand Word8
randChar = state $ randomR (32, 127)

randLine :: Int -> Int -> Rand Builder
randLine min max = do
  len <- state $ randomR (min, max)
  chars <- replicateM len randChar
  return $ mconcat $ map word8 chars

randText :: Int -> Int -> Int -> Rand Builder
randText n min max = do
  lines <- replicateM n $ randLine min max
  return $ mconcat $ intersperse (char7 '\n') lines

--{--
main = do
  (ns:maxs:mins:_) <- getArgs
  let n = read ns
      max = read maxs
      min = read mins
  txt <- getStdRandom $ runState (randText n max min)
  BS.putStr $ toLazyByteString txt
--} >
