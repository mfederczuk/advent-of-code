/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_DAY04_DAY04_UTILS_HPP
#define AOC_2021_DAY04_DAY04_UTILS_HPP

#include "bingo_board.hpp"
#include <istream>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class day04_input {
	private:
		std::vector<int> nrs;
		std::vector<bingo_board> boards;

	public:
		[[nodiscard]]
		inline day04_input() {}

		[[nodiscard]]
		const std::vector<int>& get_nrs() const {
			return nrs;
		}
		[[nodiscard]]
		std::vector<int>& get_nrs() {
			return nrs;
		}

		[[nodiscard]]
		const std::vector<bingo_board>& get_boards() const {
			return boards;
		}
		[[nodiscard]]
		std::vector<bingo_board>& get_boards() {
			return boards;
		}

		friend std::istream& operator>>(std::istream& stream, day04_input& input) {
			std::string line;
			std::getline(stream, line);

			std::istringstream line_stream(line);
			std::vector<int> nrs;

			int nr;
			while(line_stream >> nr) {
				line_stream.get(); // skip the comma
				nrs.push_back(nr);
			}


			std::vector<bingo_board> boards;

			bingo_board board;
			while(stream >> board) {
				boards.emplace_back(std::move(board));
			}


			input.nrs = std::move(nrs);
			input.boards = std::move(boards);

			return stream;
		}
};

#endif /* AOC_2021_DAY04_DAY04_UTILS_HPP */
