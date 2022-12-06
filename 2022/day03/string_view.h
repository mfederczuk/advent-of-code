/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef YEAR2022_DAY03_STRING_VIEW_H
#define YEAR2022_DAY03_STRING_VIEW_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

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
	assert(string_view_is_valid(sv));
	return (size_t)(sv.end - sv.begin);
}

static inline bool string_view_is_empty(const struct string_view sv) {
	assert(string_view_is_valid(sv));
	return (sv.begin == sv.end);
}


static inline bool string_view_contains_char(const struct string_view sv,
                                             const char ch,
                                             const size_t begin_index,
                                             size_t end_index) {

	const size_t len = string_view_length(sv);

	if ((begin_index >= end_index) || (begin_index >= len)) {
		return false;
	}

	if (end_index > len) {
		end_index = len;
	}

	for (size_t i = begin_index; i < end_index; ++i) {
		if (sv.begin[i] == ch) {
			return true;
		}
	}

	return false;
}


static inline struct string_view string_view_subview(const struct string_view sv,
                                                     size_t begin_index,
                                                     size_t length) {
	assert(string_view_is_valid(sv));

	const size_t sv_len = string_view_length(sv);

	if (sv_len == 0) {
		return sv;
	}

	if (begin_index >= sv_len) {
		begin_index = (sv_len - 1);
	}

	if (length > (sv_len - begin_index)) {
		length = (sv_len - begin_index);
	}

	return (struct string_view){
		.begin = (sv.begin + begin_index),
		.end   = (sv.begin + begin_index + length),
	};
}

#endif /* YEAR2022_DAY03_STRING_VIEW_H */
