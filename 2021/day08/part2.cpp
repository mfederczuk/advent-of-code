/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "../aoc2021.hpp"
#include <array>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <istream>
#include <ostream>
#include <string_view>
#include <string>
#include <utility>
#include <vector>

struct entry {
	std::array<std::string, 10> input_patterns;
	std::array<std::string,  4> output_patterns;

	[[nodiscard]]
	std::size_t calculate_output_value() const noexcept;

	friend std::istream& operator>>(std::istream& stream, entry& entry) {
		for(std::string& input_pattern : entry.input_patterns) {
			stream >> input_pattern;
		}

		stream >> std::ws;
		stream.ignore(1); // skip the vertical bar

		for(std::string& output_pattern : entry.output_patterns) {
			stream >> output_pattern;
		}

		return stream;
	}

	friend std::ostream& operator<<(std::ostream& stream, const entry& entry) {
		for(const std::string_view input_pattern : entry.input_patterns) {
			stream << input_pattern << ' ';
		}

		stream << '|';

		for(const std::string_view output_pattern : entry.output_patterns) {
			stream << ' ' << output_pattern;
		}

		return stream;
	}
};

std::size_t entry::calculate_output_value() const noexcept {
	// Step 1.:
	//   Find and save the patterns of digits 1, 4, 7 and 8

	std::string_view digit_1_pattern;
	std::string_view digit_4_pattern;
	std::string_view digit_7_pattern;
	std::string_view digit_8_pattern;

	{
		const std::function<void(std::string_view&, std::size_t)> find_pattern =
			[this](std::string_view& ref, const std::size_t segment_count) {
				ref =
					*std::find_if(
						input_patterns.cbegin(),
						input_patterns.cend(),
						[segment_count](const std::string_view input_pattern) -> bool {
							return (input_pattern.length() == segment_count);
						}
					);
			};

		find_pattern(digit_1_pattern, 2);
		find_pattern(digit_4_pattern, 4);
		find_pattern(digit_7_pattern, 3);
		find_pattern(digit_8_pattern, 7);
	}

	// Step 2.:
	//   Deduce the mapping of segment `a` through digits 1 and 7

	const char a = digit_7_pattern[digit_7_pattern.find_first_not_of(digit_1_pattern)];

	// Step 3.:
	//   Deduce possible mappings of segments `c` and `f` through digit 1

	const char possible_c = digit_1_pattern[0];
	const char possible_f = digit_1_pattern[1];

	// Step 4.:
	//   Find and save the pattern of digit 3 through segments `c` and `f`

	const std::string_view digit_3_pattern =
		*std::find_if(
			input_patterns.cbegin(),
			input_patterns.cend(),
			[possible_c, possible_f](const std::string_view input_pattern) -> bool {
				return (input_pattern.length() == 5 &&
				        input_pattern.find(possible_c) != std::string_view::npos &&
				        input_pattern.find(possible_f) != std::string_view::npos);
			}
		);

	// Step 5.:
	//   Deduce the mapping of segment `d` through digits 3 and 4

	const char d =
		*std::find_if(
			digit_4_pattern.cbegin(),
			digit_4_pattern.cend(),
			[possible_c, possible_f, digit_3_pattern](const char ch) -> bool {
				return (ch != possible_c &&
				        ch != possible_f &&
				        digit_3_pattern.find(ch) != std::string_view::npos);
			}
		);

	// Step 6.:
	//   Deduce the mapping of segment `g` through digit 3

	const char g = digit_3_pattern[digit_3_pattern.find_first_not_of(std::string {a, possible_c, d, possible_f})];

	// Step 7.:
	//   Deduce the mapping of segment `b` through digit 4

	const char b = digit_4_pattern[digit_4_pattern.find_first_not_of(std::string {possible_c, d, possible_f})];

	// Step 8.:
	//   Deduce the mapping of segment `e` through digit 8

	const char e = digit_8_pattern[digit_8_pattern.find_first_not_of(std::string {a, b, possible_c, d, possible_f, g})];

	// Step 9.:
	//   Deduce the actual mappings of segments `c` and `f` through digit 6

	char c;
	char f;

	for(const std::string_view input_pattern : input_patterns) {
		if(input_pattern.length() != 6) {
			// is not either 0, 6 or 9
			continue;
		}

		const bool has_possible_c = (input_pattern.find(possible_c) != std::string_view::npos);
		const bool has_possible_f = (input_pattern.find(possible_f) != std::string_view::npos);

		if(has_possible_c && has_possible_f) {
			// is either 0 or 9
			continue;
		}

		c = possible_c;
		f = possible_f;

		if(has_possible_c) {
			std::swap(c, f);
		}
	}

	std::array<std::pair<int, std::string>, 10> mapped_patterns = {
		std::pair {0, std::string {a, b, c, e, f, g}},
		std::pair {1, std::string {c, f}},
		std::pair {2, std::string {a, c, d, e, g}},
		std::pair {3, std::string {a, c, d, f, g}},
		std::pair {4, std::string {b, c, d, f}},
		std::pair {5, std::string {a, b, d, f, g}},
		std::pair {6, std::string {a, b, d, e, f, g}},
		std::pair {7, std::string {a, c, f}},
		std::pair {8, std::string {a, b, c, d, e, f, g}},
		std::pair {9, std::string {a, b, c, d, f, g}},
	};

	std::sort(
		mapped_patterns.begin(),
		mapped_patterns.end(),
		[](const std::pair<int, std::string>& p1, const std::pair<int, std::string>& p2) -> bool {
			return (p1.second.length() > p2.second.length());
		}
	);

	const std::function<int(std::string_view)> decode_pattern =
		[&mapped_patterns](const std::string_view pattern) -> int {
			for(const auto& [digit, mapped_pattern] : mapped_patterns) {
				const bool correct_pattern =
					std::all_of(
						mapped_pattern.cbegin(),
						mapped_pattern.cend(),
						[pattern](const char ch) -> bool {
							return (pattern.find(ch) != std::string_view::npos);
						}
					);

				if(correct_pattern) {
					return digit;
				}
			}

			std::abort();
		};

	std::size_t value = 0;

	for(const std::string_view output_pattern : output_patterns) {
		value = ((value * 10) + decode_pattern(output_pattern));
	}

	return value;
}

aoc2021::ANSWER aoc2021::solution(std::istream& input) {
	std::vector<entry> entries;

	for(entry entry; input >> entry; ) {
		entries.emplace_back(std::move(entry));
	}

	std::size_t output_values_sum = 0;

	for(const entry& entry : entries) {
		output_values_sum += entry.calculate_output_value();
	}

	return output_values_sum;
}
