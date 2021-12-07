/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>

constexpr inline const std::size_t last_day = 80;

int main() {
	std::ifstream input("input.txt");

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

	return 0;
}
