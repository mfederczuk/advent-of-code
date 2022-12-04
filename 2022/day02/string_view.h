/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef YEAR2022_DAY02_STRING_VIEW_H
#define YEAR2022_DAY02_STRING_VIEW_H

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

#endif /* YEAR2022_DAY02_STRING_VIEW_H */
