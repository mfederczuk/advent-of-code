/*
 * Advent of Code 2020 - Day 10 - Part 1
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

import java.io.FileInputStream
import java.util.Scanner

fun main(args: Array<String>) {
	var inputFile = "example_input_1"
	if(args.size >= 1) inputFile = args[0]

	val adapters = mutableListOf<Int>()

	Scanner(FileInputStream(inputFile)).use { f ->
		while(f.hasNext()) {
			adapters += f.nextLine().toInt()
		}
	}

	adapters += 0
	adapters.sort()
	adapters += (adapters.last() + 3)

	var diff1Jolts = 0
	var diff3Jolts = 0
	var i = 0
	while(i < (adapters.size - 1)) {
		var diff = adapters[i + 1] - adapters[i + 0]

		when(diff) {
			1 -> ++diff1Jolts
			3 -> ++diff3Jolts
		}

		++i
	}

	println(diff1Jolts * diff3Jolts)
}
