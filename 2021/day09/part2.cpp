/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "day09_utils.hpp"
#include "point.hpp"
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <functional>
#include <iostream>
#include <unordered_set>
#include <vector>

void determine_basin(
	std::unordered_set<point>& basin,
	const std::vector<std::vector<int>>& matrix,
	const point& starting_point
);

int main() {
	std::ifstream input_file("input.txt");

	day09_input input;
	input_file >> input;

	const std::vector<point> low_points = input.find_low_points();

	std::vector<std::unordered_set<point>> basins;
	basins.reserve(low_points.size());

	const std::vector<std::vector<int>>& matrix = input.matrix;

	for(const point& low_point : low_points) {
		basins.emplace_back(/* empty unordered_set */);

		determine_basin(basins.back(), matrix, low_point);
	}

	std::sort(
		basins.begin(),
		basins.end(),
		[](const std::unordered_set<point>& b1, const std::unordered_set<point>& b2) -> bool {
			return (b1.size() > b2.size());
		}
	);

	std::cout << (basins[0].size() * basins[1].size() * basins[2].size()) << '\n';

	return 0;
}

void determine_basin(
	std::unordered_set<point>& basin,
	const std::vector<std::vector<int>>& matrix,
	const point& starting_point
) {
	basin.insert(starting_point);

	const std::function<void(const point&)> maybe_determine_next_point = [&basin, &matrix](const point& next_point) {
		if((matrix[next_point.y][next_point.x] == 9) || (basin.count(next_point) > 0)) {
			return;
		}

		determine_basin(basin, matrix, next_point);
	};

	// up
	if(starting_point.y > 0) {
		maybe_determine_next_point({starting_point.x, (starting_point.y - 1)});
	}

	// right
	if((starting_point.x + 1) < matrix[starting_point.y].size()) {
		maybe_determine_next_point({(starting_point.x + 1), starting_point.y});
	}

	// down
	if((starting_point.y + 1) < matrix.size()) {
		maybe_determine_next_point({starting_point.x, (starting_point.y + 1)});
	}

	// left
	if(starting_point.x > 0) {
		maybe_determine_next_point({(starting_point.x - 1), starting_point.y});
	}
}
