/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>

int main() {
	std::ifstream input("input.txt");

	int prev_depth = std::numeric_limits<decltype(prev_depth)>::max();
	int cur_depth;
	std::size_t count = 0;

	while(input >> cur_depth) {
		count += (cur_depth > prev_depth);
		prev_depth = cur_depth;
	}

	std::cout << count << '\n';

	return 0;
}