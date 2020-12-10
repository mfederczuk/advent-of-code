/*
 * Advent of Code 2020 - Day 10 - Part 2
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

fun findArrangements(
	lastAdapter: Int,
	availableAdapters: List<Int>,
	cachedResults: MutableMap<Int, Long> = mutableMapOf()
): Long {
	if(cachedResults.containsKey(lastAdapter)) {
		return cachedResults.getValue(lastAdapter)
	}

	val fittingAdapters = availableAdapters.fold(emptyList<Int>()) { fittingAdapters, adapter ->
		if(adapter > lastAdapter && adapter <= (lastAdapter + 3)) {
			fittingAdapters + adapter
		} else {
			fittingAdapters
		}
	}

	if(fittingAdapters.isEmpty()) return 1;

	var arrangementCount = 0L

	fittingAdapters.forEach { fittingAdapter ->
		arrangementCount += findArrangements(
			fittingAdapter,
			availableAdapters.toMutableList().apply {
				removeAll { it <= fittingAdapter }
			},
			cachedResults
		)
	}

	cachedResults[lastAdapter] = arrangementCount
	return arrangementCount
}

fun main(args: Array<String>) {
	var inputFile = "example_input_1"
	if(args.size >= 1) inputFile = args[0]

	val adapters = mutableListOf<Int>()

	Scanner(FileInputStream(inputFile)).use { f ->
		while(f.hasNext()) {
			adapters += f.nextLine().toInt()
		}
	}

	adapters.sort()

	val arrangementCount = findArrangements(0, adapters)

	println(arrangementCount)
}
