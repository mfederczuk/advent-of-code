/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "bingo_board.hpp"
#include "day04_utils.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>

int main() {
	std::ifstream input_stream("input.txt");

	day04_input input;
	input_stream >> input;

	std::size_t win_count = 0;

	for(const int nr : input.get_nrs()) {
		for(bingo_board& board : input.get_boards()) {
			if(board.has_bingo()) {
				continue;
			}

			board.mark(nr);

			win_count += board.has_bingo();

			if(win_count == input.get_boards().size()) {
				std::cout << board.calculate_score(nr) << '\n';
				return 0;
			}
		}
	}

	return 0;
}
