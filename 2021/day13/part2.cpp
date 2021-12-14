/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "../aoc2021.hpp"
#include "day13_utils.hpp"
#include "point.hpp"
#include <algorithm>
#include <cstddef>
#include <istream>
#include <string>

aoc2021::ANSWER aoc2021::solution(std::istream& input_file) {
	day13_input input;
	input_file >> input;

	input.fold_all();

	const std::size_t max_x =
		std::max_element(
			input.points.cbegin(),
			input.points.cend(),
			[](const point& p1, const point& p2) -> bool {
				return (p1.x < p2.x);
			}
		)->x;

	const std::size_t max_y =
		std::max_element(
			input.points.cbegin(),
			input.points.cend(),
			[](const point& p1, const point& p2) -> bool {
				return (p1.y < p2.y);
			}
		)->y;

	std::string out;

	for(std::size_t y = 0; y <= max_y; ++y) {
		for(std::size_t x = 0; x <= max_x; ++x) {
			if(input.points.count({x, y}) > 0) {
				out += '#';
			} else {
				out += '.';
			}
		}

		out += '\n';
	}

	return out;
}
