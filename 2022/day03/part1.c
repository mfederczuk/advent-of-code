/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "dynamic_sso_string.h"
#include "file_line_iter.h"
#include "string_view_io.h"
#include "string_view.h"
#include <stdio.h>

typedef size_t prio_t;

static prio_t get_item_type_priority(const char item_type) {
	if ((item_type >= 'a') && (item_type <= 'z')) {
		return (prio_t)((item_type - 'a') + 1);
	}

	return (prio_t)((item_type - 'A') + 27);
}

int main(const int argc, const char* const* argv) {
	if (argc < 2) {
		fprintf(stderr, "%s: missing argument: <input_file>\n", argv[0]);
		return 3;
	}

	struct dynamic_sso_string duplicate_item_types;
	dynamic_sso_string_init_empty(&duplicate_item_types);

	struct file_line_iter iter;
	if (file_line_iter_init(&iter, argv[1]) != 0) {
		perror("file_line_iter_init");
		return EXIT_FAILURE;
	}

	struct file_line_iter_next next_line;
	do {
		if (file_line_iter_next(&iter, &next_line) != 0) {
			file_line_iter_destroy(&iter);
			return EXIT_FAILURE;
		}

		if (!(next_line.valid)) {
			break;
		}

		const struct string_view line = dynamic_sso_string_as_string_view(&(next_line.line));
		const size_t line_len = string_view_length(line);

		const struct string_view compartment1 = string_view_subview(line, 0, (line_len / 2));
		const struct string_view compartment2 = string_view_subview(line,    (line_len / 2), (size_t)-1);

		for (const char* it = compartment2.begin; it < compartment2.end; ++it) {
			if (string_view_contains_char(compartment1, *it, 0, (size_t)-1)) {
				if(dynamic_sso_string_append_char(&duplicate_item_types, *it) != 0) {
					perror("dynamic_sso_string_append_char");

					dynamic_sso_string_destroy(&(next_line.line));

					file_line_iter_destroy(&iter);
					dynamic_sso_string_destroy(&duplicate_item_types);

					return EXIT_FAILURE;
				}

				break;
			}
		}

		dynamic_sso_string_destroy(&(next_line.line));
	} while (1);

	file_line_iter_destroy(&iter);

	prio_t prio_sum = 0;

	for (size_t i = 0; i < duplicate_item_types.size; ++i) {
		prio_sum += get_item_type_priority(dynamic_sso_string_data_ptr(&duplicate_item_types)[i]);
	}

	dynamic_sso_string_destroy(&duplicate_item_types);

	printf("%zu\n", prio_sum);

	return 0;
}
