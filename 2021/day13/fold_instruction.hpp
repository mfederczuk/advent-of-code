/*
 * Copyright (c) 2021 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_2021_DAY13_FOLD_INSTRUCTION_HPP
#define AOC_2021_DAY13_FOLD_INSTRUCTION_HPP

#include "axis.hpp"
#include <cstddef>
#include <istream>
#include <ostream>
#include <string_view>

struct fold_instruction {
	static constexpr inline const std::string_view prefix = std::string_view("fold along ");

	::axis axis;
	std::size_t coord;

	friend std::istream& operator>>(std::istream& stream, fold_instruction& instr) {
		if(!std::istream::sentry(stream)) return stream;

		stream.ignore(prefix.size());

		stream >> instr.axis;
		stream.ignore(1); // skip equals
		stream >> instr.coord;

		return stream;
	}

	friend std::ostream& operator<<(std::ostream& stream, const fold_instruction& instr) {
		stream << prefix << instr.axis;

		return stream;
	}
};


#endif /* AOC_2021_DAY13_FOLD_INSTRUCTION_HPP */
