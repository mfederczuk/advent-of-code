/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "../aoc2021.hpp"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <functional>
#include <istream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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

struct cave_system {
	// name => cave
	std::unordered_map<std::string, cave> caves;

	[[nodiscard]]
	inline const cave& start_cave() const {
		return caves.at("start");
	}

	friend std::istream& operator>>(std::istream& stream, cave_system& system) {
		const std::function<cave&(std::string_view)> insert_cave =
			[&system](const std::string_view name) -> cave& {
				return system.caves.emplace(name, cave {static_cast<std::string>(name)}).first->second;
			};

		std::string line;
		while(std::getline(stream, line)) {
			std::string::const_iterator it = line.cbegin();

			for(; std::isalpha(*it); ++it);

			cave& from = insert_cave(std::string {line.cbegin(), it});

			++it; // skip dash

			cave& to = insert_cave(std::string {it, line.cend()});

			from.connected_caves.emplace(to);
			to.connected_caves.emplace(from);
		}

		return stream;
	}
};

struct path {
	std::vector<std::reference_wrapper<const cave>> visited_caves;

	[[nodiscard]]
	bool has_visited_cave(std::string_view name) const {
		return
			std::any_of(
				visited_caves.cbegin(),
				visited_caves.cend(),
				[name](const cave& cave) -> bool {
					return (cave.name == name);
				}
			);
	}
};

[[nodiscard]]
std::size_t find_correct_paths_count(const cave& cave_coming_into, path path_before_entering_cave) {
	path_before_entering_cave.visited_caves.emplace_back(cave_coming_into);

	std::size_t correct_paths_count = 0;

	for(const cave& connected_cave : cave_coming_into.connected_caves) {
		if(connected_cave.name == "end") {
			correct_paths_count += 1;
			continue;
		}

		if(connected_cave.is_small() && path_before_entering_cave.has_visited_cave(connected_cave.name)) {
			continue;
		}

		correct_paths_count += find_correct_paths_count(connected_cave, path_before_entering_cave);
	}

	return correct_paths_count;
}

aoc2021::ANSWER aoc2021::solution(std::istream& input) {
	cave_system system;
	input >> system;

	return find_correct_paths_count(system.start_cave(), path {});
}
