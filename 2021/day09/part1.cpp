/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

[[nodiscard]]
constexpr inline int ascii_digit_to_int(char ch) noexcept {
	return static_cast<int>(ch - 0x30);
}

template<typename T>
class optional_reference final {
	private:
		T* ptr;

	public:
		[[nodiscard]]
		constexpr inline optional_reference() noexcept : ptr(nullptr) {}

		[[nodiscard]]
		inline optional_reference(T& value) noexcept : ptr(&value) {}


		inline optional_reference& operator=(T& value) noexcept {
			this->ptr = &value;
			return *this;
		}


		[[nodiscard]]
		constexpr inline bool has_value() const noexcept {
			return (ptr != nullptr);
		}

		[[nodiscard]]
		inline T& get() noexcept {
			return *ptr;
		}

		[[nodiscard]]
		inline const T& get() const noexcept {
			return *ptr;
		}
};

int main() {
	std::ifstream input("example_input.txt");

	std::vector<std::vector<int>> matrix;

	std::string line;
	while(std::getline(input, line)) {
		matrix.emplace_back(/* empty vector */);
		matrix.back().reserve(line.length());
		for(const char ch : line) {
			matrix.back().push_back(ascii_digit_to_int(ch));
		}
	}

	std::size_t risk_level = 0;

	for(std::size_t y = 0; y < matrix.size(); ++y) {
		optional_reference<std::vector<int>> upper_row;
		const std::vector<int>& row = matrix[y];
		optional_reference<std::vector<int>> lower_row;

		if(y > 0) upper_row = matrix[y - 1];
		if((y + 1) < matrix.size()) lower_row = matrix[y + 1];

		for(std::size_t x = 0; x < row.size(); ++x) {
			const int height = row[x];

			if((upper_row.has_value()  && (upper_row.get()[x] <= height)) ||
			   (lower_row.has_value()  && (lower_row.get()[x] <= height)) ||
			   ((x > 0)                && (row[x - 1]         <= height)) ||
			   (((x + 1) < row.size()) && (row[x + 1]         <= height))) {
				continue;
			}

			risk_level += (height + 1);
		}
	}

	std::cout << risk_level << '\n';

	return 0;
}
