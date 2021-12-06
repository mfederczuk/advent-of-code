/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_DAY05_POINT_HPP
#define AOC_2021_DAY05_POINT_HPP

#include <istream>
#include <ostream>
#include <utility>

struct point {
	int x;
	int y;

	[[nodiscard]]
	constexpr bool operator==(const point& other) const noexcept {
		return (this->x == other.x && this->y == other.y);
	}

	[[nodiscard]]
	constexpr bool operator!=(const point& other) const noexcept {
		return (this->x != other.x || this->y != other.y);
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

#endif /* AOC_2021_DAY05_POINT_HPP */
