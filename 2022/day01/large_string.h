/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef YEAR2022_DAY01_LARGE_STRING_H
#define YEAR2022_DAY01_LARGE_STRING_H

#include "string_view.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

enum {
	LARGE_STRING_INIT_CAPACITY = 2048,
	LARGE_STRING_GROWTH_FACTOR = 2,
};

struct large_string {
	size_t capacity;
	size_t size;
	char* data;
};

static inline int large_string_init_empty(struct large_string* const s) {
	char* const data = malloc(sizeof (char) * LARGE_STRING_INIT_CAPACITY);

	if (data == NULL) {
		return 1;
	}

	*s = (struct large_string){
		.capacity = LARGE_STRING_INIT_CAPACITY,
		.size = 0,
		.data = data,
	};

	return 0;
}

static inline void large_string_destroy(struct large_string* const s) {
	free(s->data);
}

static inline int large_string_reserve(struct large_string* const s, const size_t required_capacity) {
	if (s->capacity >= required_capacity) {
		return 0;
	}

	size_t new_capacity = s->capacity;

	do {
		new_capacity *= LARGE_STRING_GROWTH_FACTOR;
	} while (new_capacity < required_capacity);

	char* const new_data = realloc(s->data, sizeof (char) * new_capacity);

	if (new_data == NULL) {
		return 1;
	}

	s->capacity = new_capacity;
	s->data = new_data;

	return 0;
}

static inline int large_string_append(struct large_string* const s, char* buf, size_t buf_size) {
	if (large_string_reserve(s, (s->size + buf_size)) != 0) {
		return 1;
	}

	memcpy(s->data + s->size, buf, buf_size);
	s->size += buf_size;

	return 0;
}

static inline struct string_view large_string_as_string_view(const struct large_string* const s) {
	return (struct string_view){
		.begin = s->data,
		.end   = (s->data + s->size),
	};
}

/**
 * Returns the index of the first instance of `ch` in the range `[s->data, s->data + min(end_index, s->size))` or
 * `(size_t)-1` when nothing was found.
 */
static inline size_t large_string_find_first_index_of_char(const struct large_string* const s,
                                                           const char ch,
                                                           const size_t begin_index,
                                                           const size_t end_index) {

	const struct string_view sv = large_string_as_string_view(s);
	return string_view_find_first_index_of_char(sv, ch, begin_index, end_index);
}

#endif /* YEAR2022_DAY01_LARGE_STRING_H */
