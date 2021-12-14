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
		std::string polymer = polymer_template;

		std::string new_polymer;

		for(std::size_t ni = 0; ni < n; ++ni) {
			new_polymer += polymer[0];

			for(std::size_t i = 0; i < (polymer.size() - 1); ++i) {
				const char a = polymer[i + 0];
				const char b = polymer[i + 1];

				if(insertion_rules.count({a, b}) > 0) {
					new_polymer += insertion_rules.at({a, b});
				}

				new_polymer += b;
			}

			polymer = std::move(new_polymer);
		}

		std::unordered_map<char, std::size_t> element_counts;

		for(const char element : polymer) {
			if(element_counts.count(element) > 0) {
				continue;
			}

			element_counts.emplace(
				element,
				std::count(polymer.cbegin(), polymer.cend(), element)
			);
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
