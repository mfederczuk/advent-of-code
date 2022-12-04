/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef YEAR2022_DAY01_COMMON_H
#define YEAR2022_DAY01_COMMON_H

#include "large_string.h"

#include "string_view.h"

#include "large_string_io.h"
#include "large_string_iter.h"
#include "vector_size_t.h"

static inline int year2022_day01_init_vector_size_t_with_total_elf_calories_from_file(
	struct vector_size_t* const vec,
	const char* const pathname
) {
	struct large_string file_contents;
	if (large_string_init_from_file_contents(&file_contents, pathname) != 0) {
		return 1;
	}

	struct vector_size_t total_elf_calories_vec;
	if (vector_size_t_init_empty(&total_elf_calories_vec) != 0) {
		large_string_destroy(&file_contents);
		return 1;
	}

	if (vector_size_t_append(&total_elf_calories_vec, 0) != 0) {
		vector_size_t_destroy(&total_elf_calories_vec);
		large_string_destroy(&file_contents);
		return 1;
	}

	struct large_string_line_iter line_iter = large_string_line_iter_create(&file_contents);
	do {
		const struct string_view line = large_string_line_iter_next(&line_iter);

		if (string_view_is_invalid(line)) {
			break;
		}

		if (string_view_is_empty(line)) {
			if (*(vector_size_t_last(&total_elf_calories_vec)) != 0) {
				if (vector_size_t_append(&total_elf_calories_vec, 0) != 0) {
					vector_size_t_destroy(&total_elf_calories_vec);
					large_string_destroy(&file_contents);
					return 1;
				}
			}

			continue;
		}

		char* const cstr = string_view_allocate_cstring(line);

		if (cstr == NULL) {
			vector_size_t_destroy(&total_elf_calories_vec);
			large_string_destroy(&file_contents);
			return 1;
		}

		char* endptr = NULL;
		const size_t elf_calories = (size_t)strtoull(cstr, &endptr, 10);

		if((endptr == cstr) || (*endptr != '\0')) {
			free(cstr);
			vector_size_t_destroy(&total_elf_calories_vec);
			large_string_destroy(&file_contents);
			return 1;
		}

		*(vector_size_t_last(&total_elf_calories_vec)) += elf_calories;

		free(cstr);
	} while (1);

	*vec = total_elf_calories_vec;

	large_string_destroy(&file_contents);

	return 0;
}

#endif /* YEAR2022_DAY01_COMMON_H */
