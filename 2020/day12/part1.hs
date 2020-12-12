{-
 - Advent of Code 2020 - Day 12 - Part 1
 - Copyright (C) 2020  Michael Federczuk
 -
 - This program is free software: you can redistribute it and/or modify
 - it under the terms of the GNU General Public License as published by
 - the Free Software Foundation, either version 3 of the License, or
 - (at your option) any later version.
 -
 - This program is distributed in the hope that it will be useful,
 - but WITHOUT ANY WARRANTY; without even the implied warranty of
 - MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 - GNU General Public License for more details.
 -
 - You should have received a copy of the GNU General Public License
 - along with this program.  If not, see <https://www.gnu.org/licenses/>.
 -}

import qualified Data.Text
import System.Environment (getArgs)

strip :: String -> String
strip s = Data.Text.unpack (Data.Text.strip (Data.Text.pack s))

data Action = North | East | South | West | Left | Right | Forward

type Instruction = (Action, Integer)

data State = State {north :: Integer, east :: Integer, angle :: Integer}

charToAction :: Char -> Action
charToAction 'N' = North
charToAction 'E' = East
charToAction 'S' = South
charToAction 'W' = West
charToAction 'L' = Main.Left
charToAction 'R' = Main.Right
charToAction 'F' = Forward

parseInstruction :: String -> Instruction
parseInstruction s =
  ( charToAction (head s),
    read (tail s)
  )

parseInput :: String -> [Instruction]
parseInput s = map parseInstruction (words (strip s))

calcAngle :: Integer -> Integer
calcAngle angle = mod angle 360

execInstruction :: Instruction -> State -> State
execInstruction (North, val) state = state {north = north state + val}
execInstruction (East, val) state = state {east = east state + val}
execInstruction (South, val) state = state {north = north state - val}
execInstruction (West, val) state = state {east = east state - val}
execInstruction (Main.Left, val) state = state {angle = calcAngle (angle state - val)}
execInstruction (Main.Right, val) state = state {angle = calcAngle (angle state + val)}
execInstruction (Forward, val) (State north east 0) = State {north = north + val, east = east, angle = 0}
execInstruction (Forward, val) (State north east 90) = State {north = north, east = east + val, angle = 90}
execInstruction (Forward, val) (State north east 180) = State {north = north - val, east = east, angle = 180}
execInstruction (Forward, val) (State north east 270) = State {north = north, east = east - val, angle = 270}

execInstructions :: [Instruction] -> State -> State
execInstructions [] state = state
execInstructions instructions state = execInstructions (tail instructions) (execInstruction (head instructions) state)

manhattenDistance :: Integer -> Integer -> Integer
manhattenDistance a b = a + b

getInputFilePath :: IO String
getInputFilePath = do
  args <- getArgs
  if not (null args)
    then do return $ head args
    else do return "example_input"

main :: IO ()
main = do
  inputFile <- readFile =<< getInputFilePath
  let state = execInstructions (parseInput inputFile) (State 0 0 90)
  print $ manhattenDistance (abs $ north state) (abs $ east state)
