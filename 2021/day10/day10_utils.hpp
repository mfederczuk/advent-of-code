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
	int autocomplete_points;

	[[nodiscard]]
	constexpr inline scope(const char (&open_close_chars)[3], int syntax_error_score, int autocomplete_points) noexcept
			: open_char(open_close_chars[0]),
			  close_char(open_close_chars[1]),
			  syntax_error_score(syntax_error_score),
			  autocomplete_points(autocomplete_points) {
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
	scope {"()", /* syntax_error_score: */     3, /* autocomplete_points: */ 1},
	scope {"[]", /* syntax_error_score: */    57, /* autocomplete_points: */ 2},
	scope {"{}", /* syntax_error_score: */  1197, /* autocomplete_points: */ 3},
	scope {"<>", /* syntax_error_score: */ 25137, /* autocomplete_points: */ 4},
};

#endif /* AOC_2021_DAY10_DAY10_UTILS_HPP */
