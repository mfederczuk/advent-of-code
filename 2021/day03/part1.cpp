/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "../aoc2021.hpp"
#include <cstddef>
#include <istream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

aoc2021::ANSWER aoc2021::solution(std::istream& input) {
	std::vector<std::string> binary_numbers;
	std::string line;

	while(input >> line) {
		binary_numbers.emplace_back(std::move(line));
	}

	line.clear();


	const std::size_t digit_count = binary_numbers.front().length();
	const unsigned int mask = (1 << digit_count) - 1;

	unsigned int nr = 0;
	bool is_one;
	std::size_t one_count;

	for(std::size_t digit_i = 0; digit_i < digit_count; ++digit_i) {
		one_count = 0;
		for(const std::string_view binary_number : binary_numbers) {
			one_count += (binary_number[digit_i] == '1');
		}

		is_one = (one_count > (binary_numbers.size() / 2));

		nr = (nr << 1) | is_one;
	}

	return (nr * (~nr & mask));
}
