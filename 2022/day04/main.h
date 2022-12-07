/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef YEAR2022_DAY04_MAIN_H
#define YEAR2022_DAY04_MAIN_H

#include "utils/support_types.h"
#include <stdio.h>

int aoc_main(const const_cstr_t input_file_pathname);

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

	return aoc_main(input_file_pathname);
}

#endif /* YEAR2022_DAY04_MAIN_H */
