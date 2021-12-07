/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_DAY06_DAY06_UTILS_HPP
#define AOC_2021_DAY06_DAY06_UTILS_HPP

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void print_lantern_fish(const std::string& input_file, std::size_t last_day) {
	std::ifstream input(input_file);

	std::vector<int_fast8_t> lantern_fish_timers;
	lantern_fish_timers.reserve(std::pow(last_day, 4));

	for(short int nr; input >> nr; ) {
		lantern_fish_timers.push_back(static_cast<int_fast8_t>(nr));
		input.ignore(1); // skip comma
	}

	std::size_t new_fish;

	for(std::size_t day = 1; day <= last_day; ++day) {
		const std::size_t count = lantern_fish_timers.size();

		new_fish = 0;

		for(std::size_t i = 0; i < count; ++i) {
			int_fast8_t& fish = lantern_fish_timers[i];

			if(fish == 0) {
				fish = 6;
				++new_fish;
				continue;
			}

			--fish;
		}

		lantern_fish_timers.resize(count + new_fish, 8);
	}

	std::cout << lantern_fish_timers.size() << '\n';
}

#endif /* AOC_2021_DAY06_DAY06_UTILS_HPP */
