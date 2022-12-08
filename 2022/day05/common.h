/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_YEAR2022_DAY05_COMMON_H
#define AOC_YEAR2022_DAY05_COMMON_H

#include "utils/array_utils.h"
#include "utils/dynamic_sso_string.h"
#include "utils/errno_utils.h"
#include "utils/file_line_iter.h"
#include "utils/string_view.h"
#include "utils/support_types.h"
#include "vector_dynamic_sso_string.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// man these are some great names

enum aoc_year2022_day05_init_starting_crate_stacks_vector_from_input_file_line_iter_result {
	AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_SUCCESS,
	AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_MALFORMED_INPUT_EOF,
	AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_MALFORMED_INPUT_EMPTY_LINE,
	AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_MALFORMED_INPUT_INVALID_FINAL_LINE,
	AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_MALFORMED_INPUT_INVALID_LINE,
	AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_MALFORMED_INPUT_INVALID_STACK_SEPARATOR,
	AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_FAILURE,
};

enum aoc_year2022_day05_parse_size_t_result {
	AOC_YEAR2022_DAY05_PARSE_SIZE_T_RESULT_SUCCESS,
	AOC_YEAR2022_DAY05_PARSE_SIZE_T_RESULT_INVALID_STRING,
	AOC_YEAR2022_DAY05_PARSE_SIZE_T_RESULT_FAILURE,
};

static inline enum aoc_year2022_day05_init_starting_crate_stacks_vector_from_input_file_line_iter_result
aoc_year2022_day05_init_starting_crate_stacks_vector_from_input_file_line_iter(
	struct vector_dynamic_sso_string* const crate_stacks_vector,
	struct file_line_iter* const input_file_line_iter
) {
	struct vector_dynamic_sso_string crate_stacks_vector_internal;
	if (vector_dynamic_sso_string_init_empty(&crate_stacks_vector_internal) != RET_STATUS_SUCCESS) {
		return AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_FAILURE;
	}

	// input only has at most 8 stacks: 1 to 9 (both inclusive)
	if (vector_dynamic_sso_string_reserve(&crate_stacks_vector_internal, 8) != RET_STATUS_SUCCESS) {
		errno_push();
		vector_dynamic_sso_string_destroy(&crate_stacks_vector_internal);
		errno_pop();
		return AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_FAILURE;
	}

	do {
		struct file_line_iter_next next_line;
		if (file_line_iter_next(input_file_line_iter, &next_line) != RET_STATUS_SUCCESS) {
			errno_push();

			for (size_t i = 0; i < crate_stacks_vector_internal.size; ++i) {
				dynamic_sso_string_destroy(crate_stacks_vector_internal.data + i);
			}
			vector_dynamic_sso_string_destroy(&crate_stacks_vector_internal);

			errno_pop();

			return AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_FAILURE;
		}

		if (!(next_line.valid)) {
			for (size_t i = 0; i < crate_stacks_vector_internal.size; ++i) {
				dynamic_sso_string_destroy(crate_stacks_vector_internal.data + i);
			}
			vector_dynamic_sso_string_destroy(&crate_stacks_vector_internal);

			return AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_MALFORMED_INPUT_EOF;
		}

		struct string_view line = dynamic_sso_string_as_string_view(&(next_line.str));
		line = string_view_trimmed_trailing_ws(line);

		if (string_view_is_empty(line)) {
			dynamic_sso_string_destroy(&(next_line.str));

			for (size_t i = 0; i < crate_stacks_vector_internal.size; ++i) {
				dynamic_sso_string_destroy(crate_stacks_vector_internal.data + i);
			}
			vector_dynamic_sso_string_destroy(&crate_stacks_vector_internal);

			return AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_MALFORMED_INPUT_EMPTY_LINE;
		}

		if (string_view_starts_with_cstring(line, " 1")) {
			line = string_view_subview(line, 2, (size_t)-1);

			for (size_t crate_stack_index = 1;
			     crate_stack_index < crate_stacks_vector_internal.size;
			     ++crate_stack_index) {

				char tmp[4] = "   N";
				tmp[3] = ((char)crate_stack_index + '1');

				if (!(string_view_starts_with_buf(line, tmp, array_size(tmp)))) {
					dynamic_sso_string_destroy(&(next_line.str));

					for (size_t i = 0; i < crate_stacks_vector_internal.size; ++i) {
						dynamic_sso_string_destroy(crate_stacks_vector_internal.data + i);
					}
					vector_dynamic_sso_string_destroy(&crate_stacks_vector_internal);

					return AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_MALFORMED_INPUT_INVALID_FINAL_LINE;
				}

				line = string_view_subview(line, 4, (size_t)-1);
			}

			dynamic_sso_string_destroy(&(next_line.str));

			break;
		}

		size_t crate_stack_index = 0;

		do {
			if ((line.length < 3) ||
			    !((memcmp(line.data, "   ", 3) == 0) ||
			      ((line.data[0] == '[') &&
			       ((line.data[1] >= 'A') && (line.data[1 <= 'Z'])) &&
			       (line.data[2] == ']')))) {

				dynamic_sso_string_destroy(&(next_line.str));

				for (size_t i = 0; i < crate_stacks_vector_internal.size; ++i) {
					dynamic_sso_string_destroy(crate_stacks_vector_internal.data + i);
				}
				vector_dynamic_sso_string_destroy(&crate_stacks_vector_internal);

				return AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_MALFORMED_INPUT_INVALID_LINE;
			}

			if ((crate_stack_index + 1) > crate_stacks_vector_internal.size) {
				struct dynamic_sso_string crates_stack;
				dynamic_sso_string_init_empty(&crates_stack);

				const ret_status_t ret = vector_dynamic_sso_string_append(&crate_stacks_vector_internal, crates_stack);

				if (ret != RET_STATUS_SUCCESS) {
					errno_push();

					dynamic_sso_string_destroy(&(next_line.str));

					for (size_t i = 0; i < crate_stacks_vector_internal.size; ++i) {
						dynamic_sso_string_destroy(crate_stacks_vector_internal.data + i);
					}
					vector_dynamic_sso_string_destroy(&crate_stacks_vector_internal);

					errno_pop();

					return AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_FAILURE;
				}
			}

			if (line.data[0] == '[') {
				const char crate_letter = line.data[1];
				const ret_status_t ret =
					dynamic_sso_string_append_char(
						crate_stacks_vector_internal.data + crate_stack_index,
						crate_letter
					);

				if (ret != RET_STATUS_SUCCESS) {
					errno_push();

					dynamic_sso_string_destroy(&(next_line.str));

					for (size_t i = 0; i < crate_stacks_vector_internal.size; ++i) {
						dynamic_sso_string_destroy(crate_stacks_vector_internal.data + i);
					}
					vector_dynamic_sso_string_destroy(&crate_stacks_vector_internal);

					errno_pop();

					return AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_FAILURE;
				}
			}

			line = string_view_subview(line, 3, (size_t)-1);

			if (string_view_is_empty(line)) {
				break;
			}

			if (line.data[0] != ' ') {
				dynamic_sso_string_destroy(&(next_line.str));

				for (size_t i = 0; i < crate_stacks_vector_internal.size; ++i) {
					dynamic_sso_string_destroy(crate_stacks_vector_internal.data + i);
				}
				vector_dynamic_sso_string_destroy(&crate_stacks_vector_internal);

				return AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_MALFORMED_INPUT_INVALID_STACK_SEPARATOR;
			}

			line = string_view_subview(line, 1, (size_t)-1);

			++crate_stack_index;
		} while (1);

		dynamic_sso_string_destroy(&(next_line.str));
	} while (1);

	for (size_t i = 0; i < crate_stacks_vector_internal.size; ++i) {
		dynamic_sso_string_reverse(crate_stacks_vector_internal.data + i);
	}

	*crate_stacks_vector = crate_stacks_vector_internal;

	return AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_SUCCESS;
}

static inline enum aoc_year2022_day05_parse_size_t_result aoc_year2022_day05_parse_size_t(size_t* const n_ptr,
                                                                                          const struct string_view sv) {
	assert(string_view_is_valid(sv));

	const cstr_t cstr = string_view_allocate_cstring(sv);

	if (cstr == NULL) {
		return AOC_YEAR2022_DAY05_PARSE_SIZE_T_RESULT_FAILURE;
	}

	char* endptr;

	const size_t n = (size_t)strtoull(cstr, &endptr, 10);

	const bool valid = (*endptr == '\0');
	free(cstr);

	if (!valid) {
		return AOC_YEAR2022_DAY05_PARSE_SIZE_T_RESULT_INVALID_STRING;
	}

	*n_ptr = n;

	return AOC_YEAR2022_DAY05_PARSE_SIZE_T_RESULT_SUCCESS;
}

#endif /* AOC_YEAR2022_DAY05_COMMON_H */
