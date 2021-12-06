/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "day05_utils.hpp"
#include "line.hpp"
#include "point.hpp"
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

int main() {
	std::ifstream input("input.txt");

	std::vector<line> lines;

	line line;
	while(input >> line) {
		lines.emplace_back(std::move(line));
	}

	std::cout << count_points(lines) << '\n';

	return 0;
}
