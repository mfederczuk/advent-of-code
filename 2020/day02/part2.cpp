/*
 * Copyright (c) 2020 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
	std::string input_file = "example_input";
	if(argc >= 2) input_file = argv[1];

	std::ifstream ifs(input_file);

	std::basic_string<decltype(ifs)::char_type> line;
	decltype(line)::const_iterator it;
	decltype(line)::const_iterator end;
	decltype(line)::const_iterator tmp_it;
	unsigned long pos1, pos2;
	decltype(line)::value_type ch;
	decltype(line) password;
	unsigned int valid_pws = 0;

	for(; std::getline(ifs, line).good(); ) {
		it = line.cbegin();
		end = line.cend();

		tmp_it = it;
		for(; it != end && std::isdigit(*it); ++it);
		pos1 = std::stoul(std::string(tmp_it, it));

		++it; // '-'

		tmp_it = it;
		for(; it != end && std::isdigit(*it); ++it);
		pos2 = std::stoi(std::string(tmp_it, it));

		++it; // ' '

		ch = *it;

		it += 3; // character & ": "

		password.assign(it, end);
		valid_pws += ((password[pos1 - 1] == ch) != (password[pos2 - 1] == ch));
	}

	std::cout << valid_pws << '\n';

	return 0;
}
