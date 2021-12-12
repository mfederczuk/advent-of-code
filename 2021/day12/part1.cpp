/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "../aoc2021.hpp"
#include "cave_system.hpp"
#include "path.hpp"
#include <istream>

aoc2021::ANSWER aoc2021::solution(std::istream& input) {
	cave_system system;
	input >> system;

	return find_correct_paths_count(system.start_cave(), path {});
}
