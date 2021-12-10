/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include <array>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <string_view>
#include <vector>

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

[[nodiscard]]
int calculate_syntax_error_score(const std::string_view line) {
	std::stack<scope, std::vector<scope>> scopes;

	for(const char ch : line) {
		for(const scope& defined_scope : defined_scopes) {
			if(ch == defined_scope.open_char) {
				scopes.push(defined_scope);
				break;
			}

			if(ch == defined_scope.close_char) {
				if(scopes.top() == defined_scope) {
					scopes.pop();
					break;
				}

				return defined_scope.syntax_error_score;
			}
		}
	}

	return 0;
}

int main() {
	std::ifstream input("input.txt");

	long int syntax_error_score = 0;

	std::string line;
	while(std::getline(input, line)) {
		syntax_error_score += calculate_syntax_error_score(line);
	}

	std::cout << syntax_error_score << '\n';

	return 0;
}
