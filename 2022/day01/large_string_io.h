/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef YEAR2022_DAY01_LARGE_STRING_IO_H
#define YEAR2022_DAY01_LARGE_STRING_IO_H

#include "large_string.h"
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

enum {
	LARGE_STRING_IO_TMP_BUF_SIZE = 2048,
};

static inline int large_string_append_remaining_stream_contents(struct large_string* const s, FILE* const stream) {
	char tmp_buf[LARGE_STRING_IO_TMP_BUF_SIZE];

	bool eof;
	bool err;

	do {
		const size_t readc = fread(tmp_buf, sizeof (char), (sizeof (tmp_buf) / sizeof (*tmp_buf)), stream);

		if (large_string_append(s, tmp_buf, readc) != 0) {
			return 1;
		}

		eof = feof(stream);
		err = ferror(stream);
	} while (!eof && !err);

	return err;
}

static inline int large_string_init_from_file_contents(struct large_string* const s, const char* const pathname) {
	struct large_string internal_s;
	if (large_string_init_empty(&internal_s) != 0) {
		return 1;
	}

	FILE* const file_stream = fopen(pathname, "r");
	if (file_stream == NULL) {
		const int errno_tmp = errno;
		large_string_destroy(&internal_s);
		errno = errno_tmp;
		return 1;
	}

	if (large_string_append_remaining_stream_contents(&internal_s, file_stream) != 0) {
		const int errno_tmp = errno;

		fclose(file_stream);
		large_string_destroy(&internal_s);

		errno = errno_tmp;

		return 1;
	}

	fclose(file_stream);

	*s = internal_s;

	return 0;
}

#endif /* YEAR2022_DAY01_LARGE_STRING_IO_H */
