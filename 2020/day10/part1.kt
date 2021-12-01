/*
 * Copyright (c) 2020 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
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
