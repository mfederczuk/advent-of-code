/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "../aoc2021.hpp"
#include <istream>
#include <string>

aoc2021::ANSWER aoc2021::solution(std::istream& input) {
	int aim = 0;
	int horizontal_pos = 0;
	int depth = 0;

	std::string cmd;
	int tmp;

	while(input >> cmd && input >> tmp) {
		if(cmd == "forward") {
			horizontal_pos += tmp;
			depth += (aim * tmp);
		} else if(cmd == "down") {
			aim += tmp;
		} else if(cmd == "up") {
			aim -= tmp;
		}
	}

	return (horizontal_pos * depth);
}
