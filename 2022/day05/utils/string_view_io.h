/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_YEAR2022_DAY05_UTILS_STRING_VIEW_IO_H
#define AOC_YEAR2022_DAY05_UTILS_STRING_VIEW_IO_H

#include "string_view.h"
#include "support_types.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static inline size_t fwrite_string_view(const struct string_view sv, FILE* const stream) {
	assert(string_view_is_valid(sv));

	return fwrite(sv.data, sizeof *(sv.data), sv.length, stream);
}

static inline size_t fprint_string_view(const const_cstr_t prefix,
                                        const struct string_view sv,
                                        const const_cstr_t suffix,
                                        FILE* const stream) {
	assert(string_view_is_valid(sv));

	size_t total_writec = 0;

	if (prefix != NULL) {
		const size_t prefix_len = strlen(prefix);

		const size_t writec = fwrite(prefix, sizeof *prefix, prefix_len, stream);

		if (writec != (sizeof *prefix * prefix_len)) {
			return (size_t)-1;
		}

		total_writec += prefix_len;
	}

	fputc('"', stream);
	++total_writec;

	const size_t sv_writec = fwrite_string_view(sv, stream);

	if (sv_writec != (sizeof *(sv.data) * sv.length)) {
		return (size_t)-1;
	}

	total_writec += sv_writec;

	fputc('"', stream);
	++total_writec;

	if (suffix != NULL) {
		const size_t suffix_len = strlen(suffix);

		const size_t writec = fwrite(suffix, sizeof *suffix, suffix_len, stream);

		if (writec != (sizeof *suffix * suffix_len)) {
			return (size_t)-1;
		}

		total_writec += suffix_len;
	}

	return total_writec;
}

#endif /* AOC_YEAR2022_DAY05_UTILS_STRING_VIEW_IO_H */
