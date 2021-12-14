/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_DAY13_AXIS_HPP
#define AOC_2021_DAY13_AXIS_HPP

#include <ios>
#include <istream>
#include <ostream>

enum class axis {
	x, y
};

std::istream& operator>>(std::istream& stream, axis& axis) {
	if(!std::istream::sentry(stream)) return stream;

	switch(stream.get()) {
		case('x'): { axis = axis::x; break; }
		case('y'): { axis = axis::y; break; }
		default: {
			stream.setstate(std::ios_base::failbit);
		}
	}

	return stream;
}

std::ostream& operator<<(std::ostream& stream, axis axis) {
	switch(axis) {
		case(axis::x): { stream << 'x'; break; }
		case(axis::y): { stream << 'y'; break; }
	}

	return stream;
}

#endif /* AOC_2021_DAY13_AXIS_HPP */
