/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "../aoc2021.hpp"
#include "bingo_board.hpp"
#include "day04_utils.hpp"
#include <istream>

aoc2021::ANSWER aoc2021::solution(std::istream& input_file) {
	day04_input input;
	input_file >> input;

	for(const int nr : input.get_nrs()) {
		for(bingo_board& board : input.get_boards()) {
			board.mark(nr);

			if(board.has_bingo()) {
				return board.calculate_score(nr);
			}
		}
	}

	return INVALID;
}
