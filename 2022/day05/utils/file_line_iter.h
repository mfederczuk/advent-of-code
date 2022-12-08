/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_YEAR2022_DAY05_UTILS_FILE_LINE_ITER_H
#define AOC_YEAR2022_DAY05_UTILS_FILE_LINE_ITER_H

#include "dynamic_sso_string.h"
#include "dynamic_string.h"
#include "errno_utils.h"
#include "support_types.h"
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "string_view_io.h"

enum {
	FILE_LINE_ITER_MIN_READC        = 2048,
	FILE_LINE_ITER_BACKLOG_INIT_CAP = FILE_LINE_ITER_MIN_READC,
};

struct file_line_iter {
	FILE* file_stream;
	struct dynamic_string backlog;
};

struct file_line_iter_next {
	bool valid;
	struct dynamic_sso_string str;
};


static inline ret_status_t file_line_iter_init(struct file_line_iter* const iter, const const_cstr_t file_pathname) {
	struct dynamic_string backlog;
	if (dynamic_string_init_empty(&backlog, FILE_LINE_ITER_BACKLOG_INIT_CAP) != RET_STATUS_SUCCESS) {
		return RET_STATUS_FAILURE;
	}

	FILE* const file_stream = fopen(file_pathname, "r");
	if (file_stream == NULL) {
		errno_push();
		dynamic_string_destroy(&backlog);
		errno_pop();
		return RET_STATUS_FAILURE;
	}

	*iter = (struct file_line_iter){
		.file_stream = file_stream,
		.backlog = backlog,
	};

	return RET_STATUS_SUCCESS;
}

static inline void file_line_iter_destroy(struct file_line_iter* const iter) {
	fclose(iter->file_stream);
	dynamic_string_destroy(&(iter->backlog));
}


static inline int file_line_iter_next(struct file_line_iter* const iter, struct file_line_iter_next* const next_line) {
	struct file_line_iter_next internal_next_line = {
		.valid = false,
	};

	const size_t backlog_nl_index = dynamic_string_find_first_index_of_char(&(iter->backlog), '\n');

	if (backlog_nl_index != (size_t)-1) {
		const ret_status_t ret =
			dynamic_sso_string_init_from_buf(
				&(internal_next_line.str),
				iter->backlog.data,
				backlog_nl_index
			);

		if (ret != RET_STATUS_SUCCESS) {
			return RET_STATUS_FAILURE;
		}

		dynamic_string_cut(&(iter->backlog), 0, (backlog_nl_index + 1));

		internal_next_line.valid = true;
		*next_line = internal_next_line;

		return RET_STATUS_SUCCESS;
	}

	bool eof;
	bool err;

	do {
		if ((iter->backlog.capacity - iter->backlog.size) < FILE_LINE_ITER_MIN_READC) {
			const size_t required_capacity = ((iter->backlog.capacity - iter->backlog.size) + FILE_LINE_ITER_MIN_READC);
			if (dynamic_string_reserve(&(iter->backlog), required_capacity) != RET_STATUS_SUCCESS) {
				return RET_STATUS_FAILURE;
			}
		}

		const size_t readc =
			fread(
				(iter->backlog.data + iter->backlog.size),
				sizeof (char),
				(iter->backlog.capacity - iter->backlog.size),
				iter->file_stream
			);

		iter->backlog.size += readc;

		eof = feof(iter->file_stream);
		err = ferror(iter->file_stream);

		size_t nl_index = dynamic_string_find_first_index_of_char(&(iter->backlog), '\n');

		// exclusive
		size_t end_line_index = nl_index;
		if(end_line_index == (size_t)-1 && (eof || err) && dynamic_string_is_not_empty(&(iter->backlog))) {
			end_line_index = iter->backlog.size;
		}

		if (end_line_index != (size_t)-1) {
			const ret_status_t ret =
				dynamic_sso_string_init_from_buf(
					&(internal_next_line.str),
					iter->backlog.data,
					end_line_index
				);

			if (ret != RET_STATUS_SUCCESS) {
				return RET_STATUS_FAILURE;
			}

			dynamic_string_cut(&(iter->backlog), 0, (end_line_index + 1));

			internal_next_line.valid = true;
		}
	} while (!(internal_next_line.valid) && !eof && !err);

	*next_line = internal_next_line;

	return RET_STATUS_SUCCESS;
}

#endif /* AOC_YEAR2022_DAY05_UTILS_FILE_LINE_ITER_H */
