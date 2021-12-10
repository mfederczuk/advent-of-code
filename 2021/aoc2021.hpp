/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_HPP
#define AOC_2021_HPP

#include <fstream>
#include <iostream>
#include <istream>


constexpr inline const struct {} INVALID;

inline std::ostream& operator<<(std::ostream& stream, const decltype(INVALID)&) {
	return (stream << "INVALID");
}

struct ANSWER final {
	ANSWER() = delete;
	ANSWER(const ANSWER&) = delete;
	ANSWER(ANSWER&&) = delete;

	template<typename ValueT>
	[[nodiscard]]
	inline ANSWER(const ValueT& value) {
		std::cout << value << '\n';
	}

	ANSWER& operator=(const ANSWER&) = delete;
	ANSWER& operator=(ANSWER&&) = delete;
};


ANSWER solution(std::istream& input);


int main(const int argc, const char* const* const argv) {
	if(argc > 2) {
		std::cerr << argv[0] << ": too many arguments: " << (argc - 1) << '\n';
		return 4;
	}

	std::string_view input_file = "example_input.txt";

	if(argc == 2) {
		input_file = argv[1];

		if(input_file.empty()) {
			std::cerr << argv[0] << ": argument must not be empty\n";
			return 9;
		}
	}

	std::ifstream input(static_cast<std::string>(input_file));

	if(!input.is_open()) {
		std::cerr << argv[0] << ": " << input_file << ": error opening file\n";
		return 48;
	}

	solution(input);

	return 0;
}

#endif /* AOC_2021_HPP */
