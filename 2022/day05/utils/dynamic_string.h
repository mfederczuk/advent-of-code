/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_YEAR2022_DAY05_UTILS_DYNAMIC_STRING_H
#define AOC_YEAR2022_DAY05_UTILS_DYNAMIC_STRING_H

#include "string_view.h"
#include "support_types.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifndef DYNAMIC_STRING_GROWTH_FACTOR
	#define DYNAMIC_STRING_GROWTH_FACTOR  1.5
#endif

struct dynamic_string {
	size_t capacity;
	size_t size;
	char* data;
};


static inline ret_status_t dynamic_string_init_empty(struct dynamic_string* const s, const size_t init_capacity) {
	char* data = NULL;

	if (init_capacity > 0) {
		data = malloc(sizeof (char) * init_capacity);

		if (data == NULL) {
			return RET_STATUS_FAILURE;
		}
	}

	*s = (struct dynamic_string){
		.capacity = init_capacity,
		.size = 0,
		.data = data,
	};

	return RET_STATUS_SUCCESS;
}

static inline ret_status_t dynamic_string_init_from_buf(struct dynamic_string* const s,
                                                        const char* const buf,
                                                        const size_t buf_size,
                                                        const size_t additional_capacity) {
	if (buf_size == 0) {
		return dynamic_string_init_empty(s, additional_capacity);
	}

	const size_t capacity = (buf_size + additional_capacity);

	char* const data = malloc(sizeof (char) * capacity);

	if (data == NULL) {
		return RET_STATUS_FAILURE;
	}

	memcpy(data, buf, buf_size);

	*s = (struct dynamic_string){
		.capacity = capacity,
		.size = buf_size,
		.data = data,
	};

	return RET_STATUS_SUCCESS;
}

static inline void dynamic_string_destroy(struct dynamic_string* const s) {
	free(s->data);
}


static inline struct string_view dynamic_string_as_string_view(const struct dynamic_string* const s) {
	return (struct string_view){
		.length = s->size,
		.data = s->data,
	};
}


static inline bool dynamic_string_is_empty(const struct dynamic_string* const s) {
	return (s->size == 0);
}

static inline bool dynamic_string_is_not_empty(const struct dynamic_string* const s) {
	return !(dynamic_string_is_empty(s));
}

static inline size_t dynamic_string_find_first_index_of_char(const struct dynamic_string* const s, const char ch) {
	return string_view_find_first_index_of_char(dynamic_string_as_string_view(s), ch);
}

static inline bool dynamic_string_contains_char(const struct dynamic_string* const s, const char ch) {
	return string_view_contains_char(dynamic_string_as_string_view(s), ch);
}


static inline ret_status_t dynamic_string_reserve(struct dynamic_string* const s, const size_t required_capacity) {
	if (s->capacity >= required_capacity) {
		return RET_STATUS_SUCCESS;
	}

	size_t new_capacity = s->capacity;

	do {
		new_capacity = (size_t)((double)new_capacity * DYNAMIC_STRING_GROWTH_FACTOR);
	} while (new_capacity < required_capacity);

	char* const new_data = realloc(s->data, (sizeof (char) * new_capacity));

	if (new_data == NULL) {
		return RET_STATUS_FAILURE;
	}

	s->capacity = new_capacity;
	s->data = new_data;

	return RET_STATUS_SUCCESS;
}

static inline ret_status_t dynamic_string_append_char(struct dynamic_string* const s, const char ch) {
	if (dynamic_string_reserve(s, (s->size + 1)) != RET_STATUS_SUCCESS) {
		return RET_STATUS_FAILURE;
	}

	s->data[s->size] = ch;
	++(s->size);

	return RET_STATUS_SUCCESS;
}

static inline ret_status_t dynamic_string_append_buf(struct dynamic_string* const s,
                                                     const char* const buf,
                                                     const size_t buf_size) {

	if (dynamic_string_reserve(s, (s->size + buf_size)) != RET_STATUS_SUCCESS) {
		return RET_STATUS_FAILURE;
	}

	memcpy((s->data + s->size), buf, buf_size);
	s->size += buf_size;

	return RET_STATUS_SUCCESS;
}

static inline void dynamic_string_cut(struct dynamic_string* const s, const size_t index, size_t count) {
	if ((index >= s->size) || (count == 0)) {
		return;
	}

	if (count > s->size) {
		count = s->size;
	}

	if ((index + count) >= s->size) {
		// no memmove necessary if cutting range is at the end
		s->size = index;
		return;
	}

	memmove((s->data + index), (s->data + index + count), (s->size - index - count));
	s->size -= count;
}

#endif /* AOC_YEAR2022_DAY05_UTILS_DYNAMIC_STRING_H */
