/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "../aoc2021.hpp"
#include <cstddef>
#include <istream>
#include <limits>

aoc2021::ANSWER aoc2021::solution(std::istream& input) {
	int prev_depth = std::numeric_limits<decltype(prev_depth)>::max();
	int cur_depth;
	std::size_t count = 0;

	while(input >> cur_depth) {
		count += (cur_depth > prev_depth);
		prev_depth = cur_depth;
	}

	return count;
}
