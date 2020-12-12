{-
 - Advent of Code 2020 - Day 12 - Part 2
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

data Pos = Pos {north :: Integer, east :: Integer}

data State = State {shipPos :: Pos, waypointPos :: Pos}

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
execInstruction (North, val) (State shipPos waypointPos) =
  State
    { shipPos = shipPos,
      waypointPos = waypointPos {north = north waypointPos + val}
    }
execInstruction (East, val) (State shipPos waypointPos) =
  State
    { shipPos = shipPos,
      waypointPos = waypointPos {east = east waypointPos + val}
    }
execInstruction (South, val) (State shipPos waypointPos) =
  State
    { shipPos = shipPos,
      waypointPos = waypointPos {north = north waypointPos - val}
    }
execInstruction (West, val) (State shipPos waypointPos) =
  State
    { shipPos = shipPos,
      waypointPos = waypointPos {east = east waypointPos - val}
    }
execInstruction (Main.Left, 0) state = state
execInstruction (Main.Left, 90) (State shipPos waypointPos) =
  State
    { shipPos = shipPos,
      waypointPos = waypointPos {north = east waypointPos, east = negate (north waypointPos)}
    }
execInstruction (Main.Left, 180) (State shipPos waypointPos) =
  State
    { shipPos = shipPos,
      waypointPos = waypointPos {north = negate (north waypointPos), east = negate (east waypointPos)}
    }
execInstruction (Main.Left, 270) (State shipPos waypointPos) =
  State
    { shipPos = shipPos,
      waypointPos = waypointPos {north = negate (east waypointPos), east = north waypointPos}
    }
execInstruction (Main.Right, val) state = execInstruction (Main.Left, calcAngle $ negate val) state
execInstruction (Forward, val) (State shipPos waypointPos) =
  State
    { shipPos = Pos {north = north shipPos + (north waypointPos * val), east = east shipPos + (east waypointPos * val)},
      waypointPos = waypointPos
    }

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
  let pos = shipPos $ execInstructions (parseInput inputFile) (State (Pos 0 0) (Pos 1 10))
  print $ manhattenDistance (abs $ north pos) (abs $ east pos)
