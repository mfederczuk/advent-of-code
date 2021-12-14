/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_DAY14_DAY14_UTILS_HPP
#define AOC_2021_DAY14_DAY14_UTILS_HPP

#include <algorithm>
#include <climits>
#include <cstddef>
#include <istream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

struct day14_input {
	struct char_pair_hash final {
		[[nodiscard]]
		constexpr inline std::size_t operator()(std::pair<char, char> pair) const noexcept {
			static_assert((sizeof(pair.first) + sizeof(pair.second)) <= sizeof(std::size_t));
			return ((pair.first << (sizeof(pair.second) * CHAR_BIT)) | pair.second);
		}
	};

	std::string polymer_template;
	std::unordered_map<  std::pair<char, char>,  char,  char_pair_hash  > insertion_rules;

	friend std::istream& operator>>(std::istream& stream, day14_input& input) {
		if(!std::istream::sentry(stream)) return stream;

		std::string polymer_template;
		std::getline(stream, polymer_template);

		std::unordered_map<  std::pair<char, char>,  char,  char_pair_hash  > insertion_rules;

		std::string line;
		std::pair<char, char> source;
		while(std::getline(stream, line)) {
			source.first = line[0];
			source.second = line[1];

			insertion_rules.emplace(
				std::move(source),
				line[2 + std::string_view(" -> ").size()]
			);
		}

		input.polymer_template = std::move(polymer_template);
		input.insertion_rules = std::move(insertion_rules);

		return stream;
	}

	std::size_t get_result_after_n_insertions(const std::size_t n) const {
		// gotta say, I'm actually quite proud of this solution

		std::unordered_map<  std::pair<char, char>,  std::size_t,  char_pair_hash  > pair_counts, new_pair_counts;
		std::unordered_map<char, std::size_t> element_counts;

		element_counts.emplace(polymer_template.front(), 1);

		for(std::size_t i = 0; i < (polymer_template.size() - 1); ++i) {
			const char left = polymer_template[i + 0];
			const char right = polymer_template[i + 1];

			++(pair_counts[{left, right}]);
			++(element_counts[right]);
		}

		for(std::size_t i = 0; i < n; ++i) {
			for(const auto& [pair, count] : pair_counts) {
				const char insertion_char = insertion_rules.at(pair);

				new_pair_counts[{pair.first,  insertion_char}] += count;
				new_pair_counts[{insertion_char, pair.second}] += count;

				element_counts[insertion_char] += count;
			}

			pair_counts = std::move(new_pair_counts);
		}

		const auto [min_it, max_it] =
			std::minmax_element(
				element_counts.cbegin(),
				element_counts.cend(),
				[](const std::pair<char, std::size_t>& entry1, const std::pair<char, std::size_t>& entry2) -> bool {
					return (entry1.second < entry2.second);
				}
			);

		return (max_it->second - min_it->second);
	}
};

#endif /* AOC_2021_DAY14_DAY14_UTILS_HPP */
