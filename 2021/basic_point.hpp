/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_BASIC_POINT_HPP
#define AOC_2021_BASIC_POINT_HPP

#include <cstddef>
#include <istream>
#include <ostream>
#include <utility>
#include <type_traits>

template<typename AxisT>
struct basic_point final {
	static_assert(
		(std::is_same_v<AxisT,   signed short     int> ||
		 std::is_same_v<AxisT,   signed           int> ||
		 std::is_same_v<AxisT,   signed long      int> ||
		 std::is_same_v<AxisT,   signed long long int> ||
		 std::is_same_v<AxisT, unsigned short     int> ||
		 std::is_same_v<AxisT, unsigned           int> ||
		 std::is_same_v<AxisT, unsigned long      int> ||
		 std::is_same_v<AxisT, unsigned long long int>),
		"basic_point<AxisT>: AxisT is not an integer type"
	);

	AxisT x;
	AxisT y;

	[[nodiscard]]
	constexpr bool operator==(const basic_point& other) const {
		return ((this->x == other.x) && (this->y == other.y));
	}
	[[nodiscard]]
	constexpr bool operator!=(const basic_point& other) const {
		return !(this->operator==(other));
	}

	friend std::istream& operator>>(std::istream& stream, basic_point& point) {
		return ((stream >> point.x).ignore(1) >> point.y);
	}

	friend std::ostream& operator<<(std::ostream& stream, const basic_point& point) {
		return (stream << point.x << ',' << point.y);
	}
};

template<typename AxisT>
struct std::hash<basic_point<AxisT>> final {
	[[nodiscard]]
	inline std::size_t operator()(const basic_point<AxisT>& point) const noexcept {
		const std::size_t x_hash = std::hash<AxisT>{}(point.x);
		const std::size_t y_hash = std::hash<AxisT>{}(point.y);
		return x_hash ^ (y_hash << 1);
	}
};

#endif /* AOC_2021_BASIC_POINT_HPP */
