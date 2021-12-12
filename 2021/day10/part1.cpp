/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "../aoc2021.hpp"
#include "day10_utils.hpp"
#include <istream>
#include <stack>
#include <string>
#include <string_view>
#include <vector>

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

aoc2021::ANSWER aoc2021::solution(std::istream& input) {
	long int syntax_error_score = 0;

	std::string line;
	while(std::getline(input, line)) {
		syntax_error_score += calculate_syntax_error_score(line);
	}

	return syntax_error_score;
}
