/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "../aoc2021.hpp"
#include <cstddef>
#include <istream>
#include <limits>
#include <vector>

ANSWER solution(std::istream& input) {
	std::vector<int> depths;
	for(int depth; input >> depth; ) {
		depths.push_back(depth);
	}

	long int prev_sum = std::numeric_limits<long int>::max();
	long int cur_sum;
	std::size_t count = 0;

	for(std::size_t i = 0; i < (depths.size() - 2); ++i) {
		cur_sum = (long int)(depths[i + 0]) +
		          (long int)(depths[i + 1]) +
		          (long int)(depths[i + 2]);
		count += (cur_sum > prev_sum);
		prev_sum = cur_sum;
	}

	return count;
}
