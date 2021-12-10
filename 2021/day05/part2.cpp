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

ANSWER solution(std::istream& input) {
	std::vector<line> lines;

	line line;
	while(input >> line) {
		lines.emplace_back(std::move(line));
	}

	return count_points(lines);
}
