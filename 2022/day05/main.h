/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_YEAR2022_DAY05_MAIN_H
#define AOC_YEAR2022_DAY05_MAIN_H

#include "utils/support_types.h"
#include <stdio.h>

static inline int aoc_year2022_day05_malformed_input(const const_cstr_t argv0, const const_cstr_t message) {
	if (*message == '\0') {
		fprintf(stderr, "%s: malformed input\n", argv0);
	} else {
		fprintf(stderr, "%s: malformed input: %s\n", argv0, message);
	}

	return 48;
}

int aoc_year2022_day05_main(const const_cstr_t argv0, const const_cstr_t input_file_pathname);

int main(const int argc, const const_cstr_t* const argv) {
	if (argc < 2) {
		fprintf(stderr, "%s: missing argument: <input_file>\n", argv[0]);
		return 3;
	}

	const const_cstr_t input_file_pathname = argv[1];

	if (*input_file_pathname == '\0') {
		fprintf(stderr, "%s: argument must not be empty\n", argv[0]);
		return 9;
	}

	return aoc_year2022_day05_main(argv[0], input_file_pathname);
}

#endif /* AOC_YEAR2022_DAY05_MAIN_H */
