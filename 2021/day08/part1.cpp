/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include <algorithm>
#include <array>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

constexpr inline std::array<std::size_t, 4> length_of_unique_digits {
	2, // digit 1 uses 2 segments
	4, // digit 4 ...
	3, // digit 7 ...
	7  // digit 8 ...
};

template<typename T, std::size_t N>
[[nodiscard]]
constexpr inline bool array_contains(const std::array<T, N>& array, const T& item_to_find) noexcept {
	return (std::find(array.cbegin(), array.cend(), item_to_find) != array.cend());
}

int main() {
	std::ifstream input("input.txt");

	std::size_t count = 0;

	std::string tmp;

	input.ignore(61); // beginning of line to first output digits is always 61 characters
	while(std::getline(input, tmp)) {
		std::istringstream iss(tmp);
		while(iss >> tmp) { // `tmp` can be reused here - `std::istringstream` makes a copy of the given string
			count += array_contains(length_of_unique_digits, tmp.length());
		}

		input.ignore(61);
	}

	std::cout << count << '\n';

	return 0;
}
