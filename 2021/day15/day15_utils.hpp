/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_DAY15_DAY15_UTILS_HPP
#define AOC_2021_DAY15_DAY15_UTILS_HPP

#include "../basic_matrix.hpp"
#include <istream>
#include "../basic_point.hpp"
#include <ostream>
#include <string>
#include <vector>

using risk_level_t = signed char;

using point = basic_point<std::size_t>;
using matrix = basic_matrix<risk_level_t>;

[[nodiscard]]
constexpr inline risk_level_t ascii_digit_to_risk_level(const char ch) noexcept {
	return static_cast<risk_level_t>(ch - '0');
}

std::istream& operator>>(std::istream& stream, matrix& cave) {
	std::string line;

	while(std::getline(stream, line)) {
		std::vector<risk_level_t>& row = cave.rows().emplace_back(/* empty vector */);
		row.reserve(line.length());

		for(const char ch : line) {
			row.push_back(ascii_digit_to_risk_level(ch));
		}
	}

	return stream;
}

#endif /* AOC_2021_DAY15_DAY15_UTILS_HPP */
