/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef YEAR2022_DAY01_STRING_VIEW_H
#define YEAR2022_DAY01_STRING_VIEW_H

#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct string_view {
	char* begin;
	char* end;
};

#define STRING_VIEW_INVALID  ((struct string_view){ .begin = NULL })

static inline bool string_view_is_invalid(const struct string_view sv) {
	return (sv.begin == NULL);
}

static inline bool string_view_is_valid(const struct string_view sv) {
	return !(string_view_is_invalid(sv));
}

static inline size_t string_view_length(const struct string_view sv) {
	return (size_t)(sv.end - sv.begin);
}

static inline bool string_view_is_empty(const struct string_view sv) {
	return (sv.begin == sv.end);
}

/**
 * Returns the index of the first instance of `ch` in the range `[sv.begin, min(sv.begin + end_index, sv.end))` or
 * `(size_t)-1` when nothing was found.
 */
static inline size_t string_view_find_first_index_of_char(const struct string_view sv,
                                                          const char ch,
                                                          const size_t begin_index,
                                                          size_t end_index) {
	const size_t len = string_view_length(sv);

	if ((begin_index >= end_index) ||
	    (begin_index >= len)) {

		return (size_t)-1;
	}

	if (end_index > len) {
		end_index = len;
	}

	for (size_t i = begin_index; i < end_index; ++i) {
		if (sv.begin[i] == ch) {
			return i;
		}
	}

	return (size_t)-1;
}

static inline bool string_view_contains_char(const struct string_view sv,
                                             const char ch,
                                             const size_t begin_index,
                                             const size_t end_index) {

	return (string_view_find_first_index_of_char(sv, ch, begin_index, end_index) != (size_t)-1);
}

/**
 * ERRORS:
 *  `EINVAL`  The range of `[sv.begin, sv.end)` contains a nul byte.
 *  `ERANGE`  There was not enough space to allocate the block of date because the length of the range
 *            `[sv.begin, sv.end)` is `SIZE_MAX`.
 */
static inline char* string_view_allocate_cstring(const struct string_view sv) {
	if (string_view_contains_char(sv, '\0', 0, (size_t)-1)) {
		errno = EINVAL;
		return NULL;
	}

	const size_t len = string_view_length(sv);

	if (len == SIZE_MAX) {
		errno = ERANGE;
		return NULL;
	}

	char* const cstr = malloc(sizeof(char) * (len + 1));

	if (cstr == NULL) {
		return NULL;
	}

	memcpy(cstr, sv.begin, len);
	cstr[len] = '\0';

	return cstr;
}

#endif /* YEAR2022_DAY01_STRING_VIEW_H */
