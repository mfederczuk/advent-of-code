/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "../aoc2021.hpp"
#include "../basic_point.hpp"
#include <cstddef>
#include <functional>
#include <ios>
#include <istream>
#include <sstream>
#include <string_view>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using point = basic_point<std::size_t>;

enum class axis {
	x, y
};

std::istream& operator>>(std::istream& stream, axis& axis) {
	switch(stream.get()) {
		case('x'): { axis = axis::x; break; }
		case('y'): { axis = axis::y; break; }
		default: {
			stream.setstate(std::ios_base::failbit);
		}
	}

	return stream;
}

struct fold_instruction {
	static constexpr inline const std::size_t prefix_size = std::string_view("fold along ").size();

	::axis axis;
	std::size_t coord;

	friend std::istream& operator>>(std::istream& stream, fold_instruction& instr) {
		stream.ignore(prefix_size);

		stream >> instr.axis;
		stream.ignore(1); // skip equals
		stream >> instr.coord;

		return stream;
	}
};

aoc2021::ANSWER aoc2021::solution(std::istream& input) {
	std::unordered_set<point> points;

	std::string line;
	for(point point; std::getline(input, line); ) {
		if(line.empty()) {
			break;
		}

		std::istringstream iss(line);
		iss >> point;

		points.insert(std::move(point));
	}

	std::vector<fold_instruction> fold_instructions;

	for(fold_instruction instr; input >> instr; ) {
		fold_instructions.push_back(std::move(instr));
	}

	std::unordered_set<point> new_points;

	for(const fold_instruction& fold_instruction : fold_instructions) {
		switch(fold_instruction.axis) {
			case(axis::x): {
				for(const point& point : points) {
					if(point.x < fold_instruction.coord) {
						new_points.insert(point);
					} else {
						new_points.insert({
							fold_instruction.coord - (point.x - fold_instruction.coord),
							point.y
						});
					}
				}
				break;
			}
			case(axis::y): {
				for(const point& point : points) {
					if(point.y < fold_instruction.coord){
						new_points.insert(point);
					} else {
						new_points.insert({
							point.x,
							(fold_instruction.coord - (point.y - fold_instruction.coord))
						});
					}
				}
				break;
			}
		}

		points = std::move(new_points);
		break; // just first fold instruction
		       // yes, I know that this can be done *way* simpler, but I'm gonna predict that part 2 is the same, but
		       // with all fold instructions, so I'll should be able to just remove this break be done with it
	}

	return points.size();
}
