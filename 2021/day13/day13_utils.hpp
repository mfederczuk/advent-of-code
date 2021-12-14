/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_DAY13_DAY13_UTILS_HPP
#define AOC_2021_DAY13_DAY13_UTILS_HPP

#include "point.hpp"
#include "fold_instruction.hpp"
#include <unordered_set>
#include <vector>
#include <istream>
#include <string>
#include <sstream>
#include <utility>

struct day13_input {
	std::unordered_set<point> points;
	std::vector<fold_instruction> fold_instructions;

	friend std::istream& operator>>(std::istream& stream, day13_input& input) {
		if(!std::istream::sentry(stream)) return stream;

		std::unordered_set<point> points;

		std::string line;
		for(point point; std::getline(stream, line); ) {
			if(line.empty()) {
				break;
			}

			std::istringstream iss(line);
			iss >> point;

			points.insert(std::move(point));
		}

		std::vector<fold_instruction> fold_instructions;

		for(fold_instruction instr; stream >> instr; ) {
			fold_instructions.push_back(std::move(instr));
		}

		input.points = std::move(points);
		input.fold_instructions = std::move(fold_instructions);

		return stream;
	}

	bool fold_next() {
		if(fold_instructions.empty()) {
			return false;
		}

		const fold_instruction fold_instruction = fold_instructions.front();
		fold_instructions.erase(fold_instructions.cbegin());

		std::unordered_set<point> new_points;

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

		this->points = std::move(new_points);
		return true;
	}

	inline void fold_all() {
		while(fold_next());
	}
};

#endif /* AOC_2021_DAY13_DAY13_UTILS_HPP */
