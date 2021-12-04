/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include <fstream>
#include <iostream>
#include <string>

int main() {
	std::ifstream input("input.txt");

	int horizontal_pos = 0;
	int depth = 0;

	std::string cmd;
	int tmp;

	while(input >> cmd && input >> tmp) {
		if(cmd == "forward") {
			horizontal_pos += tmp;
		} else if(cmd == "down") {
			depth += tmp;
		} else if(cmd == "up") {
			depth -= tmp;
		}
	}

	std::cout << (horizontal_pos * depth) << '\n';

	return 0;
}
