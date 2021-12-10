/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_DAY10_DAY10_UTILS_HPP
#define AOC_2021_DAY10_DAY10_UTILS_HPP

#include <array>

struct scope {
	char open_char;
	char close_char;
	int syntax_error_score;

	[[nodiscard]]
	constexpr inline scope(const char (&open_close_chars)[3], int syntax_error_score) noexcept
			: open_char(open_close_chars[0]),
			  close_char(open_close_chars[1]),
			  syntax_error_score(syntax_error_score) {
	}

	[[nodiscard]]
	constexpr inline bool operator==(const scope& other) const noexcept {
		return ((this->open_char == other.open_char) &&
		        (this->close_char == other.close_char) &&
		        (this->syntax_error_score == other.syntax_error_score));
	}

	[[nodiscard]]
	constexpr inline bool operator!=(const scope& other) const noexcept {
		return !(this->operator==(other));
	}
};

constexpr inline const std::array<scope, 4> defined_scopes = {
	scope {"()",     3},
	scope {"[]",    57},
	scope {"{}",  1197},
	scope {"<>", 25137},
};

#endif /* AOC_2021_DAY10_DAY10_UTILS_HPP */
