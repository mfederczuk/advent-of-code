/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "../aoc2021.hpp"
#include "cave_system.hpp"
#include <istream>
#include <string>
#include <unordered_map>
#include <string_view>
#include <algorithm>
#include <functional>
#include <vector>

aoc2021::ANSWER aoc2021::solution(std::istream& input) {
	cave_system system;
	input >> system;

	std::string out_string;

	out_string += "@startuml Cave System Diagram" "\n\n";

	for(auto const& [cave_name, _] : system.caves) {
		out_string += "map " + cave_name + " {" "\n"
		              "}" "\n";
	}

	out_string += '\n';

	std::unordered_multimap<std::string_view, std::string_view> written_connections;

	for(auto const& [_, cave] : system.caves) {
		if(cave.name == "end") {
			continue;
		}

		for(const ::cave& connected_cave : cave.connected_caves) {
			if(connected_cave.name == "start") {
				continue;
			}

			const auto& [begin, end] = written_connections.equal_range(connected_cave.name);
			const auto it =
				std::find_if(
					begin,
					end,
					[&cave](const std::pair<const std::string_view, std::string_view>& pair) -> bool {
						return (pair.second == cave.name);
					}
				);

			if(it != end) {
				continue;
			}

			std::string separator;
			if((cave.name == "start") || (connected_cave.name == "end")) {
				separator = " -down-> ";
			} else {
				separator = " <--> ";
			}

			out_string += cave.name + separator + connected_cave.name + '\n';

			written_connections.emplace(cave.name, connected_cave.name);
		}
	}

	out_string += "\n" "@enduml";

	return out_string;
}
