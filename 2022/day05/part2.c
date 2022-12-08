/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "main.h"

#include "common.h"
#include "utils/dynamic_sso_string.h"
#include "utils/file_line_iter.h"
#include "utils/string_view.h"
#include "vector_dynamic_sso_string.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int aoc_year2022_day05_main(const const_cstr_t argv0, const const_cstr_t input_file_pathname) {
	struct file_line_iter input_file_line_iter;
	if (file_line_iter_init(&input_file_line_iter, input_file_pathname) != RET_STATUS_SUCCESS) {
		perror("file_line_iter_init");
		return EXIT_FAILURE;
	}

	struct vector_dynamic_sso_string crate_stacks_vector;
	enum aoc_year2022_day05_init_starting_crate_stacks_vector_from_input_file_line_iter_result result =
		aoc_year2022_day05_init_starting_crate_stacks_vector_from_input_file_line_iter(
			&crate_stacks_vector,
			&input_file_line_iter
		);

	switch (result) {
		case AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_SUCCESS: {
			break;
		}
		case AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_MALFORMED_INPUT_EOF: {
			file_line_iter_destroy(&input_file_line_iter);
			return aoc_year2022_day05_malformed_input(argv0, "EOF before finished parsing starting stacks");
		}
		case AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_MALFORMED_INPUT_EMPTY_LINE: {
			file_line_iter_destroy(&input_file_line_iter);
			return aoc_year2022_day05_malformed_input(argv0, "empty line during parsing starting stacks");
		}
		case AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_MALFORMED_INPUT_INVALID_FINAL_LINE: {
			file_line_iter_destroy(&input_file_line_iter);
			return aoc_year2022_day05_malformed_input(argv0, "invalid final line of starting stacks");
		}
		case AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_MALFORMED_INPUT_INVALID_LINE: {
			file_line_iter_destroy(&input_file_line_iter);
			return aoc_year2022_day05_malformed_input(argv0, "invalid line of starting stacks");
		}
		case AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_MALFORMED_INPUT_INVALID_STACK_SEPARATOR: {
			file_line_iter_destroy(&input_file_line_iter);
			return aoc_year2022_day05_malformed_input(argv0, "stacks not separated by single space");
		}
		case AOC_YEAR2022_DAY05_INIT_STARTING_CRATE_STACKS_VECTOR_FROM_INPUT_FILE_LINE_ITER_RESULT_FAILURE: {
			perror("aoc_year2022_day05_init_starting_crate_stacks_vector_from_input_file_line_iter");
			file_line_iter_destroy(&input_file_line_iter);
			return EXIT_FAILURE;
		}
	}

	// parsing rearrangement procedure
	do {
		enum fail_reason {
			FAIL_REASON_MALFORMED_INPUT,
			FAIL_REASON_FAILURE,
		} fail_reason;

		struct file_line_iter_next next_line;
		if (file_line_iter_next(&input_file_line_iter, &next_line) != RET_STATUS_SUCCESS) {
			perror("file_line_iter_next");
			fail_reason = FAIL_REASON_FAILURE;
			goto fail;
		}

		if (!(next_line.valid)) {
			break;
		}


		struct string_view line = dynamic_sso_string_as_string_view(&(next_line.str));

		if (string_view_is_empty(line)) {
			dynamic_sso_string_destroy(&(next_line.str));
			continue;
		}


		if (!(string_view_starts_with_cstring(line, "move "))) {
			fail_reason = FAIL_REASON_MALFORMED_INPUT;
			goto fail;
		}

		line = string_view_subview(line, 5, (size_t)-1);

		size_t ws_index = string_view_find_first_index_of_ws(line);

		if ((ws_index == (size_t)-1) || (line.data[ws_index] != ' ')) {
			fail_reason = FAIL_REASON_MALFORMED_INPUT;
			goto fail;
		}


		size_t crates_count;
		enum aoc_year2022_day05_parse_size_t_result parse_result =
			aoc_year2022_day05_parse_size_t(
				&crates_count,
				string_view_subview(line, 0, ws_index)
			);

		switch (parse_result) {
			case AOC_YEAR2022_DAY05_PARSE_SIZE_T_RESULT_SUCCESS: {
				break;
			}
			case AOC_YEAR2022_DAY05_PARSE_SIZE_T_RESULT_INVALID_STRING: {
				fail_reason = FAIL_REASON_MALFORMED_INPUT;
				goto fail;
			}
			case AOC_YEAR2022_DAY05_PARSE_SIZE_T_RESULT_FAILURE: {
				perror("aoc_year2022_day05_parse_size_t");
				fail_reason = FAIL_REASON_FAILURE;
				goto fail;
			}
		}


		line = string_view_subview(line, (ws_index + 1), (size_t)-1);

		if (!(string_view_starts_with_cstring(line, "from "))) {
			fail_reason = FAIL_REASON_MALFORMED_INPUT;
			goto fail;
		}

		line = string_view_subview(line, 5, (size_t)-1);

		ws_index = string_view_find_first_index_of_ws(line);

		if ((ws_index == (size_t)-1) || (line.data[ws_index] != ' ')) {
			fail_reason = FAIL_REASON_MALFORMED_INPUT;
			goto fail;
		}


		size_t crates_stack_src_index;
		parse_result =
			aoc_year2022_day05_parse_size_t(
				&crates_stack_src_index,
				string_view_subview(line, 0, ws_index)
			);

		switch (parse_result) {
			case AOC_YEAR2022_DAY05_PARSE_SIZE_T_RESULT_SUCCESS: {
				break;
			}
			case AOC_YEAR2022_DAY05_PARSE_SIZE_T_RESULT_INVALID_STRING: {
				fail_reason = FAIL_REASON_MALFORMED_INPUT;
				goto fail;
			}
			case AOC_YEAR2022_DAY05_PARSE_SIZE_T_RESULT_FAILURE: {
				perror("aoc_year2022_day05_parse_size_t");
				fail_reason = FAIL_REASON_FAILURE;
				goto fail;
			}
		}

		if (crates_stack_src_index == 0) {
			fail_reason = FAIL_REASON_MALFORMED_INPUT;
			goto fail;
		}

		--crates_stack_src_index;


		line = string_view_subview(line, (ws_index + 1), (size_t)-1);

		if (!(string_view_starts_with_cstring(line, "to "))) {
			fail_reason = FAIL_REASON_MALFORMED_INPUT;
			goto fail;
		}

		line = string_view_subview(line, 3, (size_t)-1);


		size_t crates_stack_dest_index;
		parse_result =
			aoc_year2022_day05_parse_size_t(
				&crates_stack_dest_index,
				string_view_subview(line, 0, ws_index)
			);

		switch (parse_result) {
			case AOC_YEAR2022_DAY05_PARSE_SIZE_T_RESULT_SUCCESS: {
				break;
			}
			case AOC_YEAR2022_DAY05_PARSE_SIZE_T_RESULT_INVALID_STRING: {
				fail_reason = FAIL_REASON_MALFORMED_INPUT;
				goto fail;
			}
			case AOC_YEAR2022_DAY05_PARSE_SIZE_T_RESULT_FAILURE: {
				perror("aoc_year2022_day05_parse_size_t");
				fail_reason = FAIL_REASON_FAILURE;
				goto fail;
			}
		}

		if (crates_stack_dest_index == 0) {
			fail_reason = FAIL_REASON_MALFORMED_INPUT;
			goto fail;
		}

		--crates_stack_dest_index;


		if ((crates_stack_src_index  >= crate_stacks_vector.size) ||
		    (crates_stack_dest_index >= crate_stacks_vector.size)) {

			fail_reason = FAIL_REASON_MALFORMED_INPUT;
			goto fail;
		}

		struct dynamic_sso_string* const  src_crates_stack = (crate_stacks_vector.data + crates_stack_src_index);
		struct dynamic_sso_string* const dest_crates_stack = (crate_stacks_vector.data + crates_stack_dest_index);

		const size_t src_crates_stack_begin_index = (src_crates_stack->size - crates_count);

		const ret_status_t ret =
			dynamic_sso_string_append_buf(
				dest_crates_stack,
				(dynamic_sso_string_data_ptr(src_crates_stack) + src_crates_stack_begin_index),
				crates_count
			);

		if (ret != RET_STATUS_SUCCESS) {
			fail_reason = FAIL_REASON_FAILURE;
			goto fail;
		}

		dynamic_sso_string_cut(src_crates_stack, src_crates_stack_begin_index, (size_t)-1);


		dynamic_sso_string_destroy(&(next_line.str));

		continue;
		fail:
			dynamic_sso_string_destroy(&(next_line.str));

			for (size_t i = 0; i < crate_stacks_vector.size; ++i) {
				dynamic_sso_string_destroy(crate_stacks_vector.data + i);
			}
			vector_dynamic_sso_string_destroy(&crate_stacks_vector);

			file_line_iter_destroy(&input_file_line_iter);

			switch (fail_reason) {
				case FAIL_REASON_MALFORMED_INPUT: {
					return aoc_year2022_day05_malformed_input(argv0, "invalid rearrangement procedure line");
				}
				case FAIL_REASON_FAILURE: {
					return EXIT_FAILURE;
				}
			}
	} while (1);

	file_line_iter_destroy(&input_file_line_iter);

	char final_msg[crate_stacks_vector.size + 1];
	bool valid = true;

	for (size_t i = 0; i < crate_stacks_vector.size; ++i) {
		struct dynamic_sso_string* const crates_stack = (crate_stacks_vector.data + i);

		if (valid) {
			if (dynamic_sso_string_is_not_empty(crates_stack)) {
				final_msg[i] = dynamic_sso_string_data_ptr(crates_stack)[crates_stack->size - 1];
			} else {
				valid = false;
			}
		}

		dynamic_sso_string_destroy(crates_stack);
	}
	vector_dynamic_sso_string_destroy(&crate_stacks_vector);

	if (valid) {
		final_msg[crate_stacks_vector.size] = '\n';

		fwrite(final_msg, sizeof *final_msg, crate_stacks_vector.size + 1, stdout);
	} else {
		return aoc_year2022_day05_malformed_input(argv0, "not all stacks have a crate at the end");
	}

	return EXIT_SUCCESS;
}
