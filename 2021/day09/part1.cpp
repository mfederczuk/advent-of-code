/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "day09_utils.hpp"
#include "point.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>

int main() {
	std::ifstream input_file("input.txt");

	day09_input input;
	input_file >> input;

	std::size_t risk_level = 0;

	for(const point& point : input.find_low_points()) {
		risk_level += (input.matrix[point.y][point.x] + 1);
	}

	std::cout << risk_level << '\n';

	return 0;
}
