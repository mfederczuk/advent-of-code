/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef YEAR2022_DAY03_DYNAMIC_SSO_STRING_H
#define YEAR2022_DAY03_DYNAMIC_SSO_STRING_H

#include "string_view.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

enum {
	DYNAMIC_SSO_STRING_MIN_ARRAY_SIZE = 32,
	DYNAMIC_SSO_STRING_ARRAY_SIZE = ((sizeof (char*) < DYNAMIC_SSO_STRING_MIN_ARRAY_SIZE)
	                                 ? DYNAMIC_SSO_STRING_MIN_ARRAY_SIZE
	                                 : (sizeof (char*))),
};

#define DYNAMIC_SSO_STRING_GROWTH_FACTOR  1.5

struct dynamic_sso_string {
	size_t capacity;
	size_t size;
	union {
		char array[DYNAMIC_SSO_STRING_ARRAY_SIZE];
		char* allocated_ptr;
	} data;
};


static inline void dynamic_sso_string_init_empty(struct dynamic_sso_string* const s) {
	*s = (struct dynamic_sso_string){
		.capacity = DYNAMIC_SSO_STRING_ARRAY_SIZE,
		.size = 0,
	};
}

static inline int dynamic_sso_string_init_from_buf(struct dynamic_sso_string* const s,
                                                   const char* const buf,
                                                   const size_t buf_size) {

	if (buf_size <= DYNAMIC_SSO_STRING_ARRAY_SIZE) {
		*s = (struct dynamic_sso_string){
			.capacity = DYNAMIC_SSO_STRING_ARRAY_SIZE,
			.size = buf_size,
		};

		memcpy(s->data.array, buf, buf_size);

		return 0;
	}

	size_t capacity = (DYNAMIC_SSO_STRING_ARRAY_SIZE * DYNAMIC_SSO_STRING_GROWTH_FACTOR);
	while (capacity < buf_size) {
		capacity = (size_t)((double)capacity * DYNAMIC_SSO_STRING_GROWTH_FACTOR);
	}

	char* const allocated_data_ptr = malloc(sizeof (char) * capacity);

	if (allocated_data_ptr == NULL) {
		return 1;
	}

	memcpy(allocated_data_ptr, buf, buf_size);

	*s = (struct dynamic_sso_string){
		.capacity = capacity,
		.size = buf_size,
		.data.allocated_ptr = allocated_data_ptr,
	};

	return 0;
}

static inline void dynamic_sso_string_destroy(struct dynamic_sso_string* const s) {
	if (s->capacity <= DYNAMIC_SSO_STRING_ARRAY_SIZE) {
		return;
	}

	free(s->data.allocated_ptr);
}


static inline char* dynamic_sso_string_data_ptr(const struct dynamic_sso_string* const s) {
	if (s->capacity <= DYNAMIC_SSO_STRING_ARRAY_SIZE) {
		return (char*)(s->data.array);
	}

	return s->data.allocated_ptr;
}

static inline bool dynamic_sso_string_is_empty(const struct dynamic_sso_string* const s) {
	return (s->size > 0);
}

static inline bool dynamic_sso_string_is_not_empty(const struct dynamic_sso_string* const s) {
	return !(dynamic_sso_string_is_empty(s));
}

static inline size_t dynamic_sso_string_find_first_index_of_char(const struct dynamic_sso_string* const s,
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

	const char* const data_ptr = dynamic_sso_string_data_ptr(s);

	for (size_t i = begin_index; i < end_index; ++i) {
		if (data_ptr[i] == ch) {
			return i;
		}
	}

	return (size_t)-1;
}


static inline int dynamic_sso_string_reserve(struct dynamic_sso_string* const s, const size_t required_capacity) {
	if ((s->capacity >= required_capacity) || (required_capacity <= DYNAMIC_SSO_STRING_ARRAY_SIZE)) {
		return 0;
	}

	size_t new_capacity = s->capacity;

	do {
		new_capacity = (size_t)((double)new_capacity * DYNAMIC_SSO_STRING_GROWTH_FACTOR);
	} while (new_capacity < required_capacity);

	char* new_allocated_data_ptr;
	if (s->capacity <= DYNAMIC_SSO_STRING_ARRAY_SIZE) {
		new_allocated_data_ptr = malloc(sizeof (char) * new_capacity);

		if (new_allocated_data_ptr == NULL) {
			return 1;
		}

		memcpy(new_allocated_data_ptr, s->data.array, s->size);
	} else {
		new_allocated_data_ptr = realloc(s->data.allocated_ptr, sizeof (char) * new_capacity);

		if (new_allocated_data_ptr == NULL) {
			return 1;
		}
	}

	s->capacity = new_capacity;
	s->data.allocated_ptr = new_allocated_data_ptr;

	return 0;
}

static inline int dynamic_sso_string_append_char(struct dynamic_sso_string* const s, const char ch) {
	if (dynamic_sso_string_reserve(s, (s->size + 1)) != 0) {
		return 1;
	}

	char* const data_ptr = dynamic_sso_string_data_ptr(s);

	data_ptr[s->size] = ch;
	++(s->size);

	return 0;
}

static inline int dynamic_sso_string_append_buf(struct dynamic_sso_string* const s,
                                                const char* const buf,
                                                const size_t buf_size) {

	if (dynamic_sso_string_reserve(s, (s->size + buf_size)) != 0) {
		return 1;
	}

	char* const data_ptr = dynamic_sso_string_data_ptr(s);

	memcpy((data_ptr + s->size), buf, buf_size);
	s->size += buf_size;

	return 0;
}


static inline struct string_view dynamic_sso_string_as_string_view(const struct dynamic_sso_string* const s) {
	char* const data_ptr = dynamic_sso_string_data_ptr(s);

	return (struct string_view){
		.begin = data_ptr,
		.end = (data_ptr + s->size),
	};
}

#endif /* YEAR2022_DAY03_DYNAMIC_SSO_STRING_H */
