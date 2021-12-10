/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_DAY05_DAY05_UTILS_HPP
#define AOC_2021_DAY05_DAY05_UTILS_HPP

#include "line.hpp"
#include <algorithm>
#include <cstddef>
#include <unordered_map>
#include <utility>
#include <vector>

std::size_t count_points(const std::vector<line>& lines) {
	std::unordered_map<point, std::size_t> point_count;

	for(const line& line : lines) {
		for(line::custom_iterator it = line.get_iterator(); it.has_next(); ++it) {
			++(point_count[*it]);
		}
	}

	const std::size_t greater_than_2_count =
		std::count_if(
			point_count.cbegin(),
			point_count.cend(),
			[](const std::pair<point, std::size_t>& pair) -> bool {
				return (pair.second >= 2);
			}
		);

	return greater_than_2_count;
}

#endif /* AOC_2021_DAY05_DAY05_UTILS_HPP */
