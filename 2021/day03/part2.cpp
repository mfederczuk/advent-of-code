/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include <algorithm>
#include <cstddef>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

using bit_criteria =
	std::function<bool(
		std::size_t zero_count,
		std::size_t one_count,
		std::size_t digit_index,
		std::string_view binary_number
	)>;

bool oxygen_generator_rating_bit_criteria(
	std::size_t zero_count,
	std::size_t one_count,
	std::size_t digit_index,
	std::string_view binary_number
) {
	if(one_count >= zero_count) {
		return binary_number[digit_index] == '1';
	} else {
		return binary_number[digit_index] == '0';
	}
}

bool co2_scrubber_rating_bit_criteria(
	std::size_t zero_count,
	std::size_t one_count,
	std::size_t digit_index,
	std::string_view binary_number
) {
	if(zero_count <= one_count) {
		return binary_number[digit_index] == '0';
	} else {
		return binary_number[digit_index] == '1';
	}
}

[[nodiscard]]
int find_value(const std::vector<std::string>& binary_numbers, bit_criteria bit_criteria);

int main() {
	std::ifstream input("input.txt");

	std::vector<std::string> binary_numbers;
	std::string line;

	while(input >> line) {
		binary_numbers.emplace_back(std::move(line));
	}

	const int oxygen_generator_rating = find_value(binary_numbers, oxygen_generator_rating_bit_criteria);
	const int co2_scrubber_rating     = find_value(binary_numbers, co2_scrubber_rating_bit_criteria);

	std::cout << (oxygen_generator_rating * co2_scrubber_rating) << '\n';
}


[[nodiscard]]
int find_value(std::vector<std::string_view> binary_numbers, bit_criteria bit_criteria);

[[nodiscard]]
int find_value(const std::vector<std::string>& binary_numbers, bit_criteria bit_criteria) {
	std::vector<std::string_view> copy;
	copy.reserve(binary_numbers.size());

	for(const std::string_view binary_number : binary_numbers) {
		copy.emplace_back(std::move(binary_number));
	}

	return find_value(std::move(copy), bit_criteria);
}


[[nodiscard]]
constexpr int binary_number_to_int(const std::string_view s) {
	int n = 0;

	for(const char ch : s) {
		n = (n << 1) | (ch == '1');
	}

	return n;
}

[[nodiscard]]
int find_value(std::vector<std::string_view> binary_numbers, bit_criteria bit_criteria) {
	std::size_t digit_i = 0;
	std::size_t zero_count, one_count;

	while(binary_numbers.size() > 1) {
		zero_count =
			std::count_if(
				binary_numbers.cbegin(),
				binary_numbers.cend(),
				[digit_i](const std::string_view binary_number) -> bool {
					return (binary_number[digit_i] == '0');
				}
			);

		one_count = (binary_numbers.size() - zero_count);

		for(std::size_t i = 0; i < binary_numbers.size(); ) {
			if(bit_criteria(zero_count, one_count, digit_i, binary_numbers[i])) {
				binary_numbers.erase(binary_numbers.cbegin() + i);
			} else {
				++i;
			}
		}

		++digit_i;
	}

	return binary_number_to_int(binary_numbers[0]);
}
