/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_DAY12_CAVE_HPP
#define AOC_2021_DAY12_CAVE_HPP

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <functional>
#include <string>
#include <unordered_set>

struct cave {
	private:
		struct name_hash {
			[[nodiscard]]
			inline std::size_t operator()(const cave& cave) const {
				return std::unordered_set<std::string>::hasher{}(cave.name);
			}
		};

		struct name_equal_to {
			[[nodiscard]]
			inline bool operator()(const cave& cave1, const cave& cave2) const {
				return std::unordered_set<std::string>::key_equal{}(cave1.name, cave2.name);
			}
		};

	public:
		const std::string name;
		std::unordered_set<std::reference_wrapper<const cave>, name_hash, name_equal_to> connected_caves {};

		[[nodiscard]]
		bool is_big() const noexcept {
			return
				std::all_of(
					name.cbegin(),
					name.cend(),
					[](const char ch) -> bool {
						return std::isupper(ch);
					}
				);
		}

		[[nodiscard]]
		inline bool is_small() const noexcept {
			return !is_big();
		}
};

#endif /* AOC_2021_DAY12_CAVE_HPP */
