/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef YEAR2022_DAY04_UTILS_STRING_VIEW_H
#define YEAR2022_DAY04_UTILS_STRING_VIEW_H

#include "support_types.h"
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct string_view {
	size_t length;
	char* data;
};


#define STRING_VIEW_INVALID  ((struct string_view){ .length = (size_t)-1, .data = NULL })

static inline bool string_view_is_invalid(const struct string_view sv) {
	return ((sv.length > 0) && (sv.data == NULL));
}

static inline bool string_view_is_valid(const struct string_view sv) {
	return !(string_view_is_invalid(sv));
}


static inline bool string_view_is_empty(const struct string_view sv) {
	assert(string_view_is_valid(sv));
	return (sv.length == 0);
}

static inline bool string_view_is_not_empty(const struct string_view sv) {
	assert(string_view_is_valid(sv));
	return !(string_view_is_empty(sv));
}


static inline size_t string_view_find_first_index_of_char(const struct string_view sv, const char ch) {
	assert(string_view_is_valid(sv));

	for (size_t i = 0; i < sv.length; ++i) {
		if (sv.data[i] == ch) {
			return i;
		}
	}

	return (size_t)-1;
}

static inline bool string_view_contains_char(const struct string_view sv, const char ch) {
	assert(string_view_is_valid(sv));

	return (string_view_find_first_index_of_char(sv, ch) != (size_t)-1);
}


static inline struct string_view string_view_subview(const struct string_view sv, size_t index, size_t length) {
	assert(string_view_is_valid(sv));

	if (sv.length == 0) {
		return sv;
	}

	if (index >= sv.length) {
		index = (sv.length - 1);
	}

	if (length > (sv.length - index)) {
		length = (sv.length - index);
	}

	return (struct string_view){
		.length = length,
		.data = (sv.data + index),
	};
}


/**
 * ERRORS:
 *  `EINVAL`  The range of `[sv.data, sv.data + sv.length)` contains a nul byte.
 *  `ERANGE`  There was not enough space to allocate the block of date because the length of the range
 *            `[sv.data, sv.data + sv.length)` is `SIZE_MAX`.
 */
static inline cstr_t string_view_allocate_cstring(const struct string_view sv) {
	if (string_view_contains_char(sv, '\0')) {
		errno = EINVAL;
		return NULL;
	}

	if (sv.length == SIZE_MAX) {
		errno = ERANGE;
		return NULL;
	}

	const cstr_t cstr = malloc(sizeof (char) * (sv.length + 1));

	if (cstr == NULL) {
		return NULL;
	}

	memcpy(cstr, sv.data, sv.length);
	cstr[sv.length] = '\0';

	return cstr;
}

#endif /* YEAR2022_DAY04_UTILS_STRING_VIEW_H */
