/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_YEAR2022_DAY05_UTILS_STRING_VIEW_H
#define AOC_YEAR2022_DAY05_UTILS_STRING_VIEW_H

#include "support_types.h"
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/**
 * Represents a read-only view of a string.
 * The source may or may not be null-terminated. If it is, then the terminating null byte is NOT included in this view.
 *
 * If the `length` field is 0, then the view is empty.
 * In this state, the `data` field MAY be uninitialized, `NULL`, an invalid pointer or a valid pointer, which means that
 * the application MUST NOT refer to the `data` field.
 *
 * If the `length` field is greater than 0 and the `data` field is `NULL`, then the view is said to be "invalid".
 * Passing an invalid string view to all but 2 `string_view_*` functions is considered undefined behavior.
 * The application MUST make sure that no invalid view is ever passed to these functions.
 * The only two functions which MAY receive an invalid string view are `string_view_is_invalid` and
 * `string_view_is_valid`.
 */
struct string_view {
	size_t length;
	const char* data;
};


#define STRING_VIEW_INVALID  ((struct string_view){ .length = (size_t)-1, .data = NULL })

static inline bool string_view_is_invalid(const struct string_view sv) {
	return ((sv.length > 0) && (sv.data == NULL));
}

static inline bool string_view_is_valid(const struct string_view sv) {
	return !(string_view_is_invalid(sv));
}


#define STRING_VIEW_EMPTY  ((struct string_view){ .length = 0 })

static inline struct string_view string_view_create_from_buf(const char* const buf, const size_t buf_size) {
	assert((buf_size == 0) || (buf != NULL));

	return (struct string_view){
		.length = buf_size,
		.data = buf,
	};
}

static inline struct string_view string_view_create_from_cstring(const const_cstr_t cstr) {
	assert(cstr != NULL);

	return (struct string_view){
		.length = strlen(cstr),
		.data = cstr,
	};
}

static inline struct string_view string_view_create_from_char_ptr(const char* const char_ptr) {
	assert(char_ptr != NULL);

	return (struct string_view){
		.length = 1,
		.data = char_ptr,
	};
}


static inline bool string_view_is_empty(const struct string_view sv) {
	assert(string_view_is_valid(sv));
	return (sv.length == 0);
}

static inline bool string_view_is_not_empty(const struct string_view sv) {
	assert(string_view_is_valid(sv));
	return !(string_view_is_empty(sv));
}


static inline bool string_view_equals(const struct string_view a, const struct string_view b) {
	assert(string_view_is_invalid(a));
	assert(string_view_is_invalid(b));

	if (a.length != b.length) {
		return false;
	}

	return (memcmp(a.data, b.data, a.length) == 0);
}

static inline bool string_view_starts_with_sv(const struct string_view sv, const struct string_view prefix_sv) {
	assert(string_view_is_valid(sv));
	assert(string_view_is_valid(prefix_sv));

	if (prefix_sv.length > sv.length) {
		return false;
	}

	return (memcmp(sv.data, prefix_sv.data, prefix_sv.length) == 0);
}

static inline bool string_view_starts_with_buf(const struct string_view sv,
                                               const char* const buf,
                                               const size_t buf_size) {
	assert(string_view_is_valid(sv));
	assert((buf_size == 0) || (buf != NULL));

	return string_view_starts_with_sv(sv, string_view_create_from_buf(buf, buf_size));
}

static inline bool string_view_starts_with_cstring(const struct string_view sv, const const_cstr_t prefix_cstr) {
	assert(string_view_is_valid(sv));

	return string_view_starts_with_sv(sv, string_view_create_from_cstring(prefix_cstr));
}

static inline bool string_view_starts_with_char(const struct string_view sv, const char prefix_ch) {
	assert(string_view_is_valid(sv));

	return (string_view_is_not_empty(sv) && (sv.data[0] == prefix_ch));
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

static inline size_t string_view_find_first_index_of_ws(const struct string_view sv) {
	assert(string_view_is_valid(sv));

	for (size_t i = 0; i < sv.length; ++i) {
		if (isspace(sv.data[i])) {
			return i;
		}
	}

	return (size_t)-1;
}

static inline bool string_view_contains_char(const struct string_view sv, const char ch) {
	assert(string_view_is_valid(sv));

	return (string_view_find_first_index_of_char(sv, ch) != (size_t)-1);
}


static inline struct string_view string_view_subview(const struct string_view sv, const size_t index, size_t length) {
	assert(string_view_is_valid(sv));

	// this condition also checks for empty strings
	if (index >= sv.length) {
		return STRING_VIEW_EMPTY;
	}

	if (length > (sv.length - index)) {
		length = (sv.length - index);
	}

	return (struct string_view){
		.length = length,
		.data = (sv.data + index),
	};
}

static inline struct string_view string_view_trimmed_ws(const struct string_view sv) {
	assert(string_view_is_valid(sv));

	if (string_view_is_empty(sv)) {
		return sv;
	}

	size_t begin_index = 0;
	while ((begin_index < sv.length) && isspace(sv.data[begin_index])) {
		++begin_index;
	}

	if (begin_index >= sv.length) {
		// string only contains ws chars
		return (struct string_view){
			.length = 0,
		};
	}

	size_t end_index = (sv.length - 1);
	while ((end_index > begin_index) && isspace(sv.data[end_index])) {
		--end_index;
	}

	return (struct string_view){
		.length = ((end_index - begin_index) + 1),
		.data = (sv.data + begin_index),
	};
}

static inline struct string_view string_view_trimmed_trailing_ws(const struct string_view sv) {
	assert(string_view_is_valid(sv));

	if (string_view_is_empty(sv)) {
		return sv;
	}

	size_t end_index = sv.length;
	while ((end_index > 0) && isspace(sv.data[end_index - 1])) {
		--end_index;
	}

	if ((end_index == 0) && isspace(sv.data[0])) {
		// string only contains ws chars
		return (struct string_view){
			.length = 0,
		};
	}

	return (struct string_view){
		.length = end_index,
		.data = sv.data,
	};
}

/**
 * ERRORS:
 *  `EINVAL`  The range of `[sv.data, sv.data + sv.length)` contains a nul byte.
 *  `ERANGE`  There was not enough space to allocate the block of date because the length of the range
 *            `[sv.data, sv.data + sv.length)` is `SIZE_MAX`.
 */
static inline cstr_t string_view_allocate_cstring(const struct string_view sv) {
	assert(string_view_is_valid(sv));

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

#endif /* AOC_YEAR2022_DAY05_UTILS_STRING_VIEW_H */
