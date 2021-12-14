/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "../aoc2021.hpp"
#include "day14_utils.hpp"
#include <istream>

aoc2021::ANSWER aoc2021::solution(std::istream& input_file) {
	day14_input input;
	input_file >> input;

	return input.get_result_after_n_insertions(40);
}
