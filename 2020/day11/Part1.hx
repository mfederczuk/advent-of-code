/*
 * Advent of Code 2020 - Day 11 - Part 1
 * Copyright (C) 2020  Michael Federczuk
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

import sys.io.Process;
import haxe.display.Position.Range;
import haxe.iterators.StringIterator;

using StringTools;

enum Tile {
	FLOOR;
	EMPTY_SEAT;
	OCCUPIED_SEAT;
}

class Pos {
	public final x: Int;
	public final y: Int;

	public function new(x: Int, y: Int) {
		this.x = x;
		this.y = y;
	}
}

class Part1 {
	static function isOccupiedSeatAt(layout: Array<Array<Tile>>, y: Int, x: Int): Bool {
		final row = layout[y];
		return (row != null && row[x] == Tile.OCCUPIED_SEAT);
	}

	static final adjacentPositions = [
		new Pos(-1, -1), new Pos(0, -1), new Pos(1, -1),
		new Pos(-1,  0),                 new Pos(1,  0),
		new Pos(-1,  1), new Pos(0,  1), new Pos(1,  1)
	];

	public static function main() {
		var inputFile = "example_input";
		if(Sys.args().length >= 1) inputFile = Sys.args()[0];

		var layout = new Array<Array<Tile>>();

		for(line in sys.io.File.getContent(inputFile).trim().split("\n")) {
			layout.push(new Array());

			for(ch in new StringIterator(line)) {
				final tile = switch(String.fromCharCode(ch)) {
					case("."): Tile.FLOOR;
					case("L"): Tile.EMPTY_SEAT;
					case(_): throw null;
				}

				layout[layout.length - 1].push(tile);
			}
		}

		var layoutChanged;
		do {
			final newLayout = new Array<Array<Tile>>();
			// manual copy because Array#copy is shallow
			for(row in layout) {
				newLayout.push(new Array());

				for(tile in row) {
					newLayout[newLayout.length - 1].push(tile);
				}
			}

			layoutChanged = false;

			for(y in 0...layout.length) {
				final row = layout[y];

				for(x in 0...row.length) {
					final tile = row[x];

					if(tile == Tile.EMPTY_SEAT) {
						var allAdjacentSeatsNotOccupied = true;

						for(adjacentPosition in adjacentPositions) {
							if(isOccupiedSeatAt(layout, y + adjacentPosition.y, x + adjacentPosition.x)) {
								allAdjacentSeatsNotOccupied = false;
								break;
							}
						}

						if(allAdjacentSeatsNotOccupied) {
							newLayout[y][x] = Tile.OCCUPIED_SEAT;
							layoutChanged = true;
						}
					} else if(tile == Tile.OCCUPIED_SEAT) {
						var adjacentOccupiedSeatsCount = 0;

						for(adjacentPosition in adjacentPositions) {
							if(isOccupiedSeatAt(layout, y + adjacentPosition.y, x + adjacentPosition.x)) {
								++adjacentOccupiedSeatsCount;

								if(adjacentOccupiedSeatsCount >= 4) {
									newLayout[y][x] = Tile.EMPTY_SEAT;
									layoutChanged = true;
									break;
								}
							}
						}
					}
				}
			}

			layout = newLayout;
		} while(layoutChanged);

		var occupiedSeatsCount = 0;
		for(row in layout) {
			for(tile in row) {
				if(tile == Tile.OCCUPIED_SEAT) ++occupiedSeatsCount;
			}
		}

		Sys.println(occupiedSeatsCount);
	}
}
