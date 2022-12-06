/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef YEAR2022_DAY03_FILE_LINE_ITER_H
#define YEAR2022_DAY03_FILE_LINE_ITER_H

#include "dynamic_sso_string.h"
#include "dynamic_string.h"
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

enum {
	FILE_LINE_ITER_BACKLOG_INIT_CAP = 2048,
	FILE_LINE_ITER_MIN_READC        = 2048,
};

struct file_line_iter {
	FILE* file_stream;
	struct dynamic_string backlog;
};

struct file_line_iter_next {
	bool valid;
	struct dynamic_sso_string line;
};

static inline int file_line_iter_init(
	struct file_line_iter* const iter,
	const char* const pathname
) {
	struct dynamic_string backlog;
	if (dynamic_string_init_empty(&backlog, FILE_LINE_ITER_BACKLOG_INIT_CAP) != 0) {
		return 1;
	}

	FILE* const file_stream = fopen(pathname, "r");
	if (file_stream == NULL) {
		const int errno_tmp = errno;
		dynamic_string_destroy(&backlog);
		errno = errno_tmp;
		return 1;
	}

	*iter = (struct file_line_iter){
		.file_stream = file_stream,
		.backlog = backlog,
	};

	return 0;
}

static inline int file_line_iter_next(struct file_line_iter* const iter, struct file_line_iter_next* const next) {
	struct file_line_iter_next internal_next = {
		.valid = false,
	};

	const size_t backlog_nl_index = dynamic_string_find_first_index_of_char(&(iter->backlog), '\n', 0, (size_t)-1);

	if (backlog_nl_index != (size_t)-1) {
		if (dynamic_sso_string_init_from_buf(&(internal_next.line), iter->backlog.data, backlog_nl_index) != 0) {
			return 1;
		}

		dynamic_string_cut(&(iter->backlog), 0, (backlog_nl_index + 1));

		internal_next.valid = true;
		*next = internal_next;

		return 0;
	}

	bool eof;
	bool err;

	do {
		if ((iter->backlog.capacity - iter->backlog.size) < FILE_LINE_ITER_MIN_READC) {
			const size_t required_capacity = ((iter->backlog.capacity - iter->backlog.size) + FILE_LINE_ITER_MIN_READC);
			if (dynamic_string_reserve(&(iter->backlog), required_capacity) != 0) {
				return 1;
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

		size_t nl_index = dynamic_string_find_first_index_of_char(&(iter->backlog), '\n', 0, (size_t)-1);

		if ((nl_index == (size_t)-1) && (eof || err)) {
			nl_index = (readc - 1);
		}

		if (nl_index != (size_t)-1) {
			if (dynamic_sso_string_init_from_buf(&(internal_next.line), iter->backlog.data, nl_index) != 0) {
				return 1;
			}

			dynamic_string_cut(&(iter->backlog), 0, (nl_index + 1));

			internal_next.valid = true;
		}
	} while (!(internal_next.valid) && !eof && !err);

	*next = internal_next;

	return 0;
}

static inline void file_line_iter_destroy(struct file_line_iter* const iter) {
	fclose(iter->file_stream);
	dynamic_string_destroy(&(iter->backlog));
}

#endif /* YEAR2022_DAY03_FILE_LINE_ITER_H */
