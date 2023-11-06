/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_DAY09_DAY09_UTILS_HPP
#define AOC_2021_DAY09_DAY09_UTILS_HPP

#include "../basic_matrix.hpp"
#include "../optional_reference.hpp"
#include "point.hpp"
#include <cstddef>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

struct day09_input {
	private:
		[[nodiscard]]
		static constexpr inline int ascii_digit_to_int(char ch) noexcept {
			return static_cast<int>(ch - 0x30);
		}

		static void print_row(std::ostream& stream, const std::vector<int>& row) {
			for(const int height : row) {
				stream << height;
			}
		}

	public:
		basic_matrix<int> matrix;

		[[nodiscard]]
		std::vector<point> find_low_points() const {
			std::vector<point> points;

			for(std::size_t y = 0; y < matrix.rows_count(); ++y) {
				optional_reference<const std::vector<int>> upper_row;
				const std::vector<int>& row = matrix[y];
				optional_reference<const std::vector<int>> lower_row;

				if(y > 0) upper_row = matrix[y - 1];
				if((y + 1) < matrix.rows_count()) lower_row = matrix[y + 1];

				for(std::size_t x = 0; x < row.size(); ++x) {
					const int height = row[x];

					if((upper_row.has_value()  && (upper_row.get()[x] <= height)) ||
					   (lower_row.has_value()  && (lower_row.get()[x] <= height)) ||
					   ((x > 0)                && (row[x - 1]         <= height)) ||
					   (((x + 1) < row.size()) && (row[x + 1]         <= height))) {
						continue;
					}

					points.push_back({x, y});
				}
			}

			return points;
		}

		friend std::istream& operator>>(std::istream& stream, day09_input& input) {
			std::string line;

			while(std::getline(stream, line)) {
				input.matrix.rows().emplace_back(/* empty vector */);
				input.matrix.rows().back().reserve(line.length());

				for(const char ch : line) {
					input.matrix.rows().back().push_back(ascii_digit_to_int(ch));
				}
			}

			return stream;
		}

		friend std::ostream& operator<<(std::ostream& stream, const day09_input& input) {
			if(!input.matrix.rows().empty()) {
				print_row(stream, input.matrix.rows().front());
			}

			for(const std::vector<int>& row : input.matrix) {
				stream << '\n';
				print_row(stream, row);
			}

			return stream;
		}
};

#endif /* AOC_2021_DAY09_DAY09_UTILS_HPP */
