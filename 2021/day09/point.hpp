/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_DAY09_POINT_HPP
#define AOC_2021_DAY09_POINT_HPP

#include <cstddef>
#include <ostream>
#include <utility>

struct point {
	std::size_t x, y;

	[[nodiscard]]
	constexpr inline bool operator==(const point& other) const noexcept {
		return ((this->x == other.x) && (this->y == other.y));
	}
	[[nodiscard]]
	constexpr inline bool operator!=(const point& other) const noexcept {
		return !(this->operator==(other));
	}

	friend std::ostream& operator<<(std::ostream& stream, const point& point) {
		return (stream << '(' << point.x << '|' << point.y << ')');
	}
};

template<>
struct std::hash<point> {
	[[nodiscard]]
	inline std::size_t operator()(const point& point) const noexcept {
		const std::size_t x_hash = std::hash<std::size_t>{}(point.x);
		const std::size_t y_hash = std::hash<std::size_t>{}(point.y);
		return x_hash ^ (y_hash << 1);
	}
};

#endif /* AOC_2021_DAY09_POINT_HPP */
