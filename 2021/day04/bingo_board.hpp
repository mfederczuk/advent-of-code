/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_DAY04_BINGO_BOARD_HPP
#define AOC_2021_DAY04_BINGO_BOARD_HPP

#include <algorithm>
#include <array>
#include <cstddef>
#include <functional>
#include <iomanip>
#include <istream>
#include <ostream>

class bingo_board {
	private:
		class tile {
			private:
				int nr;
				bool marked = false;

			public:
				[[nodiscard]]
				explicit constexpr tile(int nr = 0) : nr(nr) {}

				[[nodiscard]]
				constexpr int get_nr() const {
					return nr;
				}
				[[nodiscard]]
				constexpr bool is_marked() const {
					return marked;
				}

				constexpr void set_nr(int nr) {
					this->nr = nr;
				}
				constexpr void mark() {
					marked = true;
				}

				friend std::istream& operator>>(std::istream& stream, tile& tile) {
					return (stream >> tile.nr);
				}

				friend std::ostream& operator<<(std::ostream& stream, tile tile) {
					return (stream << std::setw(2) << std::setfill(' ') << tile.nr);
				}
		};

		std::array<std::array<tile, 5>, 5> rows;

	public:
		[[nodiscard]]
		constexpr bingo_board() : rows() {}
		[[nodiscard]]
		constexpr bingo_board(bingo_board&& other) : rows(std::move(other.rows)) {}

		void mark(int nr) {
			for(std::array<tile, 5>& row : rows) {
				for(tile& tile : row) {
					if(tile.get_nr() == nr) {
						tile.mark();
					}
				}
			}
		}

		[[nodiscard]]
		constexpr bool has_bingo() const {
			for(const std::array<tile, 5>& row : rows) {
				if(std::all_of(row.cbegin(), row.cend(), std::mem_fn(&tile::is_marked))) {
					return true;
				}
			}

			for(std::size_t column_index = 0; column_index < 5; ++column_index) {
				const bool column_complete =
					std::all_of(
						rows.cbegin(),
						rows.cend(),
						[column_index](const std::array<tile, 5>& row) -> bool {
							return row[column_index].is_marked();
						}
					);

				if(column_complete) {
					return true;
				}
			}

			return false;
		}

		[[nodiscard]]
		constexpr long int calculate_score(int winning_nr) const {
			long int score = 0;

			for(const std::array<tile, 5>& row : rows) {
				for(const tile& tile : row) {
					score += (!tile.is_marked() * tile.get_nr());
				}
			}

			score *= winning_nr;

			return score;
		}

		friend std::istream& operator>>(std::istream& stream, bingo_board& board) {
			for(std::size_t row_index = 0; row_index < 5; ++row_index) {
				for(std::size_t column_index = 0; column_index < 5; ++column_index) {
					stream >> board.rows[row_index][column_index];
				}
			}

			return stream;
		}

		friend std::ostream& operator<<(std::ostream& stream, const bingo_board& board) {
			print_row(stream, board.rows.front());

			for(std::size_t row_index = 1; row_index < 5; ++row_index) {
				stream << '\n';
				print_row(stream, board.rows[row_index]);
			}

			return stream;
		}

	private:
		static void print_row(std::ostream& stream, const std::array<tile, 5>& row) {
			const auto orig_width = stream.width(2);
			const auto orig_fill = stream.fill(' ');

			stream << row.front();

			for(std::size_t column_index = 1; column_index < 5; ++column_index) {
				stream << ' ' << row[column_index];
			}

			stream.fill(orig_fill);
			stream.width(orig_width);
		}
};

#endif /* AOC_2021_DAY04_BINGO_BOARD_HPP */
