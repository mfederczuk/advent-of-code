/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <unordered_map>
#include <utility>
#include <vector>

struct point {
	int x;
	int y;

	[[nodiscard]]
	constexpr bool operator==(const point& other) const noexcept {
		return (this->x == other.x && this->y == other.y);
	}

	friend std::istream& operator>>(std::istream& stream, point& point) {
		stream >> point.x;
		stream.ignore(1); // skip comma
		stream >> point.y;
		return stream;
	}

	friend std::ostream& operator<<(std::ostream& stream, const point& point) {
		return (stream << point.x << ',' << point.y);
	}
};

template<>
struct std::hash<point> {
	[[nodiscard]]
	inline std::size_t operator()(const point& point) const noexcept {
		const std::size_t x_hash = std::hash<int>{}(point.x);
		const std::size_t y_hash = std::hash<int>{}(point.y);
		return x_hash ^ (y_hash << 1);
	}
};

struct line {
	point begin;
	point end;

	friend std::istream& operator>>(std::istream& stream, line& line) {
		stream >> line.begin;
		stream.ignore(4); // skip " -> "
		stream >> line.end;
		return stream;
	}

	friend std::ostream& operator<<(std::ostream& stream, const line& line) {
		return (stream << line.begin << " -> " << line.end);
	}
};

int main() {
	std::ifstream input("input.txt");

	std::vector<line> lines;

	line line;
	while(input >> line) {
		if(line.begin.x == line.end.x) {
			if(line.begin.y > line.end.y) {
				std::swap(line.begin.y, line.end.y);
			}
		} else if(line.begin.y == line.end.y) {
			if(line.begin.x > line.end.x) {
				std::swap(line.begin.x, line.end.x);
			}
		} else {
			// not horizontal or vertical line; ignore
			continue;
		}

		lines.emplace_back(std::move(line));
	}

	std::unordered_map<point, std::size_t> point_count;

	int i;
	for(const ::line& line : lines) {
		if(line.begin.x == line.end.x) {
			for(i = line.begin.y; i <= line.end.y; ++i) {
				++(point_count[point { line.begin.x, i }]);
			}
		} else {
			for(i = line.begin.x; i <= line.end.x; ++i) {
				++(point_count[point { i, line.begin.y }]);
			}
		}
	}

	const std::size_t greater_than_2_count =
		std::count_if(
			point_count.cbegin(),
			point_count.cend(),
			[](const std::pair<point, std::size_t>& pair) -> bool {
				return (pair.second >= 2);
			}
		);

	std::cout << greater_than_2_count << '\n';

	return 0;
}
