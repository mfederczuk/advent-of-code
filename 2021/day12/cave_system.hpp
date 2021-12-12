/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_DAY12_CAVE_SYSTEM_HPP
#define AOC_2021_DAY12_CAVE_SYSTEM_HPP

#include "cave.hpp"
#include <cctype>
#include <functional>
#include <istream>
#include <string>
#include <string_view>
#include <unordered_map>

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

#endif /* AOC_2021_DAY12_CAVE_SYSTEM_HPP */
