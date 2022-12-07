/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "main.h"

#include "utils/array_utils.h"
#include "utils/dynamic_sso_string.h"
#include "utils/file_line_iter.h"
#include "utils/string_view.h"
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct size_t_closed_range {
	size_t begin;
	size_t end;
};

#define SIZE_T_CLOSED_RANGE_INVALID  ((struct size_t_closed_range){ .begin = (size_t)-1 })

static bool size_t_closed_range_is_invalid(const struct size_t_closed_range range) {
	return (range.begin == (size_t)-1);
}

static struct size_t_closed_range parse_size_t_closed_range(const struct string_view sv) {
	const size_t sep_char_index = string_view_find_first_index_of_char(sv, '-');

	if (sep_char_index == (size_t)-1) {
		errno = EINVAL;
		return SIZE_T_CLOSED_RANGE_INVALID;
	}

	struct string_view limit_svs[] = {
		string_view_subview(sv, 0, sep_char_index),
		string_view_subview(sv, (sep_char_index + 1), (size_t)-1),
	};

	if (string_view_is_empty(limit_svs[0]) || string_view_is_empty(limit_svs[1])) {
		errno = EINVAL;
		return SIZE_T_CLOSED_RANGE_INVALID;
	}

	char* endptr;

	size_t limits[array_size(limit_svs)];

	for (size_t i = 0; i < array_size(limit_svs); ++i) {
		const cstr_t cstr = string_view_allocate_cstring(limit_svs[i]);
		if (cstr == NULL) {
			return SIZE_T_CLOSED_RANGE_INVALID;
		}

		limits[i] = (size_t)strtoull(cstr, &endptr, 10);

		const bool valid = (*endptr == '\0');
		free(cstr);

		if (!valid) {
			errno = EINVAL;
			return SIZE_T_CLOSED_RANGE_INVALID;
		}
	}

	return (struct size_t_closed_range){
		.begin = limits[0],
		.end = limits[1],
	};
}

static bool size_t_closed_range_is_subset_of(const struct size_t_closed_range a, const struct size_t_closed_range b) {
	return ((a.begin >= b.begin) && (a.end <= b.end));
}

int aoc_main(const char* const input_file_pathname) {
	size_t range_subsets_count = 0;

	struct file_line_iter input_file_line_iter;
	if (file_line_iter_init(&input_file_line_iter, input_file_pathname) != RET_STATUS_SUCCESS) {
		perror("file_line_iter_init");
		return EXIT_FAILURE;
	}

	do {
		struct file_line_iter_next next_line;
		if (file_line_iter_next(&input_file_line_iter, &next_line) != RET_STATUS_SUCCESS) {
			perror("file_line_iter_next");
			file_line_iter_destroy(&input_file_line_iter);
			return EXIT_FAILURE;
		}

		if (!(next_line.valid)) {
			break;
		}

		const struct string_view line = dynamic_sso_string_as_string_view(&(next_line.str));

		if (string_view_is_empty(line)) {
			continue;
		}

		const size_t elf_ranges_sep_char_index = string_view_find_first_index_of_char(line, ',');

		if (elf_ranges_sep_char_index == (size_t)-1) {
			fputs("Malformed input line\n", stderr);
			dynamic_sso_string_destroy(&(next_line.str));
			file_line_iter_destroy(&input_file_line_iter);
			return EXIT_FAILURE;
		}

		const struct string_view elf1_range_sv = string_view_subview(line, 0, elf_ranges_sep_char_index);
		const struct string_view elf2_range_sv = string_view_subview(line, (elf_ranges_sep_char_index + 1), (size_t)-1);

		const struct size_t_closed_range elf1_range = parse_size_t_closed_range(elf1_range_sv);
		const struct size_t_closed_range elf2_range = parse_size_t_closed_range(elf2_range_sv);

		if (size_t_closed_range_is_invalid(elf1_range) || size_t_closed_range_is_invalid(elf2_range)) {
			if (errno == EINVAL) {
				fputs("Malformed input line\n", stderr);
			} else {
				perror("parse_size_t_closed_range");
			}

			dynamic_sso_string_destroy(&(next_line.str));
			file_line_iter_destroy(&input_file_line_iter);

			return EXIT_FAILURE;
		}

		if (size_t_closed_range_is_subset_of(elf1_range, elf2_range) ||
		    size_t_closed_range_is_subset_of(elf2_range, elf1_range)) {

			++range_subsets_count;
		}

		dynamic_sso_string_destroy(&(next_line.str));
	} while (1);

	file_line_iter_destroy(&input_file_line_iter);

	printf("%zu\n", range_subsets_count);

	return EXIT_SUCCESS;
}
