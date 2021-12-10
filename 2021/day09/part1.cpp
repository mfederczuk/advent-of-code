/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "../aoc2021.hpp"
#include "day09_utils.hpp"
#include "point.hpp"
#include <cstddef>
#include <istream>

ANSWER solution(std::istream& input_file) {
	day09_input input;
	input_file >> input;

	std::size_t risk_level = 0;

	for(const point& point : input.find_low_points()) {
		risk_level += (input.matrix[point.y][point.x] + 1);
	}

	return risk_level;
}
