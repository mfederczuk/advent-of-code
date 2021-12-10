/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "day10_utils.hpp"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <optional>
#include <stack>
#include <string>
#include <string_view>
#include <vector>

[[nodiscard]]
std::optional<long int> calculate_autocomplete_score(const std::string_view line) {
	std::stack<scope, std::vector<scope>> scopes;

	for(const char ch : line) {
		for(const scope& defined_scope : defined_scopes) {
			if(ch == defined_scope.open_char) {
				scopes.push(defined_scope);
				break;
			}

			if(ch == defined_scope.close_char) {
				if(scopes.top() != defined_scope) {
					return std::nullopt;
				}

				scopes.pop();
			}
		}
	}

	int_least64_t score = 0;

	do {
		score = (score * 5) + scopes.top().autocomplete_points;
		scopes.pop();
	} while(!scopes.empty());

	return score;
}

int main() {
	std::ifstream input("input.txt");

	std::vector<int_least64_t> autocomplete_scores;

	std::string line;
	std::optional<int_least64_t> optional_score;
	while(std::getline(input, line)) {
		optional_score = calculate_autocomplete_score(line);

		if(optional_score.has_value()) {
			autocomplete_scores.push_back(optional_score.value());
		}
	}

	std::sort(autocomplete_scores.begin(), autocomplete_scores.end());

	const int_least64_t middle_score = autocomplete_scores[(autocomplete_scores.size() - 1) / 2];

	std::cout << middle_score << '\n';

	return 0;
}
