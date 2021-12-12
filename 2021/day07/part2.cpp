/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "../aoc2021.hpp"
#include <algorithm>
#include <cstddef>
#include <istream>
#include <limits>
#include <vector>

[[nodiscard]]
std::size_t calculate_fuel(const std::vector<int>& crab_positions, int test_position) {
	std::size_t fuel = 0;
	std::size_t tmp;

	for(const int crab_position : crab_positions) {
		const auto [min, max] = std::minmax(crab_position, test_position);
		tmp = (max - min);
		for(std::size_t i = 1; i <= tmp; ++i) {
			fuel += i;
		}
	}

	return fuel;
}

aoc2021::ANSWER aoc2021::solution(std::istream& input) {
	std::vector<int> crab_positions;

	int crab_position;
	while(input >> crab_position) {
		crab_positions.push_back(crab_position);
		input.ignore(1); // skip comma
	}

	std::size_t least_fuel = std::numeric_limits<std::size_t>::max();
	std::size_t fuel;

	const auto [min_crab_position, max_crab_position] =
		std::minmax_element(crab_positions.cbegin(), crab_positions.cend());

	for(int crab_position = *min_crab_position; crab_position <= *max_crab_position; ++crab_position) {
		fuel = calculate_fuel(crab_positions, crab_position);

		if(fuel < least_fuel) {
			least_fuel = fuel;
		}
	}

	return least_fuel;
}
