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
	bool has_visited_small_cave_twice = false;

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

enum class small_cave_visit_policy {
	every_once, // Part 1
	single_twice_other_once, // Part 2
};

[[nodiscard]]
std::size_t find_correct_paths_count(
	const cave& cave_coming_into,
	path path_before_entering_cave,
	small_cave_visit_policy small_cave_visit_policy
) {
	path_before_entering_cave.visited_caves.emplace_back(cave_coming_into);

	std::size_t correct_paths_count = 0;

	for(const cave& connected_cave : cave_coming_into.connected_caves) {
		path current_path = path_before_entering_cave;

		if(connected_cave.name == "end") {
			++correct_paths_count;
			continue;
		}

		if(connected_cave.is_small() && current_path.has_visited_cave(connected_cave.name)) {
			if((small_cave_visit_policy == small_cave_visit_policy::every_once) ||
			   (connected_cave.name == "start") ||
			   current_path.has_visited_small_cave_twice) {

				continue;
			}

			current_path.has_visited_small_cave_twice = true;
		}

		correct_paths_count +=
			find_correct_paths_count(
				connected_cave,
				current_path,
				small_cave_visit_policy
			);
	}

	return correct_paths_count;
}

#endif /* AOC_2021_DAY12_PATH_HPP */
