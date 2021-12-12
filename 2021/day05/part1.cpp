/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "../aoc2021.hpp"
#include "day05_utils.hpp"
#include "line.hpp"
#include <istream>
#include <utility>
#include <vector>

aoc2021::ANSWER aoc2021::solution(std::istream& input) {
	std::vector<line> lines;

	line line;
	while(input >> line) {
		if(!(line.begin.x == line.end.x || line.begin.y == line.end.y)) {
			// not horizontal or vertical line; ignore
			continue;
		}

		lines.emplace_back(std::move(line));
	}

	return count_points(lines);
}
