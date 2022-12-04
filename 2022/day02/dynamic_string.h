/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef YEAR2022_DAY02_DYNAMIC_STRING_H
#define YEAR2022_DAY02_DYNAMIC_STRING_H

#include "string_view.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define DYNAMIC_STRING_GROWTH_FACTOR 1.5

struct dynamic_string {
	size_t capacity;
	size_t size;
	char* data;
};


static inline int dynamic_string_init_empty(struct dynamic_string* const s, const size_t init_capacity) {
	char* data = NULL;

	if (init_capacity > 0) {
		data = malloc(sizeof (char) * init_capacity);

		if (data == NULL) {
			return 1;
		}
	}

	*s = (struct dynamic_string){
		.capacity = init_capacity,
		.size = 0,
		.data = data,
	};

	return 0;
}

static inline int dynamic_string_init_from_buf(struct dynamic_string* const s,
                                               const char* const buf,
                                               const size_t buf_size,
                                               const size_t additional_capacity) {
	if (buf_size == 0) {
		return dynamic_string_init_empty(s, additional_capacity);
	}

	const size_t capacity = (buf_size + additional_capacity);

	char* const data = malloc(sizeof (char) * capacity);

	if (data == NULL) {
		return 1;
	}

	memcpy(data, buf, buf_size);

	*s = (struct dynamic_string){
		.capacity = capacity,
		.size = buf_size,
		.data = data,
	};

	return 0;
}

static inline void dynamic_string_destroy(struct dynamic_string* const s) {
	free(s->data);
}


static inline bool dynamic_string_is_empty(const struct dynamic_string* const s) {
	return (s->size > 0);
}

static inline bool dynamic_string_is_not_empty(const struct dynamic_string* const s) {
	return !(dynamic_string_is_empty(s));
}

static inline size_t dynamic_string_find_first_index_of_char(const struct dynamic_string* const s,
                                                             const char ch,
                                                             const size_t begin_index,
                                                             size_t end_index) {
	if ((begin_index >= end_index) ||
	    (begin_index >= s->size)) {

		return (size_t)-1;
	}

	if (end_index > s->size) {
		end_index = s->size;
	}

	for (size_t i = begin_index; i < end_index; ++i) {
		if (s->data[i] == ch) {
			return i;
		}
	}

	return (size_t)-1;
}


static inline int dynamic_string_reserve(struct dynamic_string* const s, const size_t required_capacity) {
	if (s->capacity >= required_capacity) {
		return 0;
	}

	size_t new_capacity = s->capacity;

	do {
		new_capacity = (size_t)((double)new_capacity * DYNAMIC_STRING_GROWTH_FACTOR);
	} while (new_capacity < required_capacity);

	char* const new_data = realloc(s->data, (sizeof (char) * new_capacity));

	if (new_data == NULL) {
		return 1;
	}

	s->capacity = new_capacity;
	s->data = new_data;

	return 0;
}

static inline int dynamic_string_append(struct dynamic_string* const s, const char* const buf, const size_t buf_size) {
	if (dynamic_string_reserve(s, (s->size + buf_size)) != 0) {
		return 1;
	}

	memcpy((s->data + s->size), buf, buf_size);
	s->size += buf_size;

	return 0;
}

static inline void dynamic_string_cut(struct dynamic_string* const s, const size_t index, const size_t count) {
	if ((index >= s->size) || (count == 0)) {
		return;
	}

	// no memmove necessary if cutting range is at the end
	if ((index + count) >= s->size) {
		s->size = index;
		return;
	}

	memmove((s->data + index), (s->data + index + count), (s->size - index - count));
	s->size -= count;
}


static inline struct string_view dynamic_string_as_string_view(const struct dynamic_string* const s) {
	return (struct string_view){
		.begin = s->data,
		.end = (s->data + s->size),
	};
}

#endif /* YEAR2022_DAY02_DYNAMIC_STRING_H */
