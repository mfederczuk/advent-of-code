/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_DAY06_DAY06_UTILS_HPP
#define AOC_2021_DAY06_DAY06_UTILS_HPP

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void print_lantern_fish(const std::string& input_file, std::size_t last_day) {
	std::ifstream input(input_file);

	std::vector<int> lantern_fish_timers;

	for(int nr; input >> nr; ) {
		lantern_fish_timers.push_back(nr);
		input.ignore(1); // skip comma
	}

	for(std::size_t day = 1; day <= last_day; ++day) {
		const std::size_t count = lantern_fish_timers.size();

		for(std::size_t i = 0; i < count; ++i) {
			int& fish = lantern_fish_timers[i];

			if(fish == 0) {
				fish = 6;
				lantern_fish_timers.push_back(8);
				continue;
			}

			--fish;
		}
	}

	std::cout << lantern_fish_timers.size() << '\n';
}

#endif /* AOC_2021_DAY06_DAY06_UTILS_HPP */
