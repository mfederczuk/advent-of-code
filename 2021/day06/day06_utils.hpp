/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_DAY06_DAY06_UTILS_HPP
#define AOC_2021_DAY06_DAY06_UTILS_HPP

#include <cstddef>
#include <cstdint>
#include <istream>
#include <unordered_map>
#include <vector>

/**
 * The "hashing" function for the cached lantern fish timer keys.
 */
template<typename T>
struct same_int {
	constexpr inline std::size_t operator()(T t) const noexcept {
		return static_cast<std::size_t>(t);
	}
};

using cache_map = std::unordered_map<int_fast8_t, std::size_t, same_int<int_fast8_t>>;

std::size_t calculate_lantern_fish_population(std::istream& input, std::size_t day_count) {
	cache_map cached_results;
	cached_results.reserve(7);

	std::size_t total = 0;

	std::vector<int_fast8_t> lantern_fish_timers;
	lantern_fish_timers.reserve(0x7FFFFFFF);

	std::size_t new_fish;

	for(short int nr; input >> nr; ) {
		input.ignore(1); // skip comma

		if(cached_results.count(nr) > 0) {
			total += cached_results[nr];
			continue;
		}

		lantern_fish_timers.push_back(nr);

		for(std::size_t day = 1; day <= day_count; ++day) {
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

		total += (cached_results[nr] = lantern_fish_timers.size());

		// this shouldn't touch the capacity
		lantern_fish_timers.clear();
	}

	return total;
}

#endif /* AOC_2021_DAY06_DAY06_UTILS_HPP */
