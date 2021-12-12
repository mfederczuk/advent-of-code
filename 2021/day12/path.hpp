/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_DAY12_PATH_HPP
#define AOC_2021_DAY12_PATH_HPP

#include "cave.hpp"
#include <cstddef>
#include <functional>
#include <string_view>
#include <vector>

struct path {
	std::vector<std::reference_wrapper<const cave>> visited_caves;

	[[nodiscard]]
	bool has_visited_cave(std::string_view name) const {
		return
			std::any_of(
				visited_caves.cbegin(),
				visited_caves.cend(),
				[name](const cave& cave) -> bool {
					return (cave.name == name);
				}
			);
	}
};

[[nodiscard]]
std::size_t find_correct_paths_count(const cave& cave_coming_into, path path_before_entering_cave) {
	path_before_entering_cave.visited_caves.emplace_back(cave_coming_into);

	std::size_t correct_paths_count = 0;

	for(const cave& connected_cave : cave_coming_into.connected_caves) {
		if(connected_cave.name == "end") {
			correct_paths_count += 1;
			continue;
		}

		if(connected_cave.is_small() && path_before_entering_cave.has_visited_cave(connected_cave.name)) {
			continue;
		}

		correct_paths_count += find_correct_paths_count(connected_cave, path_before_entering_cave);
	}

	return correct_paths_count;
}

#endif /* AOC_2021_DAY12_PATH_HPP */
