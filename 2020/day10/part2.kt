/*
 * Copyright (c) 2020 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
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
