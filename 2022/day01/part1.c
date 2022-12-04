/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "large_string.h"

#include "string_view.h"

#include "large_string_io.h"
#include "large_string_iter.h"
#include "vector_size_t.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
	if (argc < 2) {
		fprintf(stderr, "%s: missing argument: <input_file>\n", argv[0]);
		return 3;
	}

	struct large_string input_contents;
	if (large_string_init_from_file_contents(&input_contents, argv[1]) != 0) {
		perror("large_string_init_from_file_contents");
		return EXIT_FAILURE;
	}

	struct vector_size_t total_elf_calories_vec;
	if (vector_size_t_init_empty(&total_elf_calories_vec) != 0) {
		perror("vector_size_t_init_empty");
		large_string_destroy(&input_contents);
		return EXIT_FAILURE;
	}

	if (vector_size_t_append(&total_elf_calories_vec, 0) != 0) {
		perror("vector_size_t_append");

		vector_size_t_destroy(&total_elf_calories_vec);
		large_string_destroy(&input_contents);

		return EXIT_FAILURE;
	}

	struct large_string_line_iter line_iter = large_string_line_iter_create(&input_contents);
	do {
		const struct string_view line = large_string_line_iter_next(&line_iter);

		if (string_view_is_invalid(line)) {
			break;
		}

		if (string_view_is_empty(line)) {
			if (*(vector_size_t_last(&total_elf_calories_vec)) != 0) {
				if (vector_size_t_append(&total_elf_calories_vec, 0) != 0) {
					perror("vector_size_t_append");

					vector_size_t_destroy(&total_elf_calories_vec);
					large_string_destroy(&input_contents);

					return EXIT_FAILURE;
				}
			}

			continue;
		}

		char* const cstr = string_view_allocate_cstring(line);

		if (cstr == NULL) {
			perror("string_view_allocate_cstring");

			vector_size_t_destroy(&total_elf_calories_vec);
			large_string_destroy(&input_contents);

			return EXIT_FAILURE;
		}

		char* endptr = NULL;
		const size_t elf_calories = (size_t)strtoull(cstr, &endptr, 10);

		if((endptr == cstr) || (*endptr != '\0')) {
			free(cstr);
			vector_size_t_destroy(&total_elf_calories_vec);
			large_string_destroy(&input_contents);
			return EXIT_FAILURE;
		}

		*(vector_size_t_last(&total_elf_calories_vec)) += elf_calories;

		free(cstr);
	} while (1);

	size_t max_total_calories = 0;

	for (size_t i = 0; i < total_elf_calories_vec.size; ++i) {
		if (total_elf_calories_vec.data[i] > max_total_calories) {
			max_total_calories = total_elf_calories_vec.data[i];
		}
	}

	printf("%zu\n", max_total_calories);

	vector_size_t_destroy(&total_elf_calories_vec);
	large_string_destroy(&input_contents);

	return EXIT_SUCCESS;
}
