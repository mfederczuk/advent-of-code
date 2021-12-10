/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "../aoc2021.hpp"
#include "bingo_board.hpp"
#include "day04_utils.hpp"
#include <cstddef>
#include <istream>

ANSWER solution(std::istream& input_file) {
	day04_input input;
	input_file >> input;

	std::size_t win_count = 0;

	for(const int nr : input.get_nrs()) {
		for(bingo_board& board : input.get_boards()) {
			if(board.has_bingo()) {
				continue;
			}

			board.mark(nr);

			win_count += board.has_bingo();

			if(win_count == input.get_boards().size()) {
				return board.calculate_score(nr);
			}
		}
	}

	return INVALID;
}
