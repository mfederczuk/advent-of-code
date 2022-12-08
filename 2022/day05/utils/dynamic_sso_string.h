/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_YEAR2022_DAY05_UTILS_DYNAMIC_SSO_STRING_H
#define AOC_YEAR2022_DAY05_UTILS_DYNAMIC_SSO_STRING_H

#include "string_view.h"
#include "support_types.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifndef DYNAMIC_SSO_STRING_MIN_ARRAY_SIZE
	#define DYNAMIC_SSO_STRING_MIN_ARRAY_SIZE  32
#endif

#ifndef DYNAMIC_SSO_STRING_GROWTH_FACTOR
	#define DYNAMIC_SSO_STRING_GROWTH_FACTOR  1.5
#endif

enum {
	DYNAMIC_SSO_STRING_ARRAY_SIZE = ((sizeof (char*) < DYNAMIC_SSO_STRING_MIN_ARRAY_SIZE)
	                                 ? DYNAMIC_SSO_STRING_MIN_ARRAY_SIZE
	                                 : (sizeof (char*))),
};

struct dynamic_sso_string {
	size_t capacity;
	size_t size;
	union {
		char array[DYNAMIC_SSO_STRING_ARRAY_SIZE];
		char* allocated_ptr;
	} data;
};


#define DYNAMIC_SSO_STRING_INVALID  ((struct dynamic_sso_string){ .capacity = 0 })

static inline bool dynamic_sso_string_is_invalid(const struct dynamic_sso_string* const s) {
	return (s->capacity == 0);
}

static inline bool dynamic_sso_string_is_valid(const struct dynamic_sso_string* const s) {
	return !(dynamic_sso_string_is_invalid(s));
}


static inline void dynamic_sso_string_init_empty(struct dynamic_sso_string* const s) {
	*s = (struct dynamic_sso_string){
		.capacity = DYNAMIC_SSO_STRING_ARRAY_SIZE,
		.size = 0,
	};
}

static inline ret_status_t dynamic_sso_string_init_from_buf(struct dynamic_sso_string* const s,
                                                            const char* const buf,
                                                            const size_t buf_size) {
	if (buf_size <= DYNAMIC_SSO_STRING_ARRAY_SIZE) {
		*s = (struct dynamic_sso_string){
			.capacity = DYNAMIC_SSO_STRING_ARRAY_SIZE,
			.size = buf_size,
		};

		memcpy(s->data.array, buf, buf_size);

		return RET_STATUS_SUCCESS;
	}

	size_t capacity = (DYNAMIC_SSO_STRING_ARRAY_SIZE * DYNAMIC_SSO_STRING_GROWTH_FACTOR);
	while (capacity < buf_size) {
		capacity = (size_t)((double)capacity * DYNAMIC_SSO_STRING_GROWTH_FACTOR);
	}

	char* const allocated_data_ptr = malloc(sizeof (char) * capacity);

	if (allocated_data_ptr == NULL) {
		return RET_STATUS_FAILURE;
	}

	memcpy(allocated_data_ptr, buf, buf_size);

	*s = (struct dynamic_sso_string){
		.capacity = capacity,
		.size = buf_size,
		.data.allocated_ptr = allocated_data_ptr,
	};

	return RET_STATUS_SUCCESS;
}

static inline ret_status_t dynamic_sso_string_init_from_cstring(struct dynamic_sso_string* const s,
                                                                const const_cstr_t cstr) {
	const size_t len = strlen(cstr);
	return dynamic_sso_string_init_from_buf(s, cstr, len);
}

static inline void dynamic_sso_string_destroy(struct dynamic_sso_string* const s) {
	assert(dynamic_sso_string_is_valid(s));

	if (s->capacity <= DYNAMIC_SSO_STRING_ARRAY_SIZE) {
		return;
	}

	free(s->data.allocated_ptr);
}


static inline char* dynamic_sso_string_data_ptr(const struct dynamic_sso_string* const s) {
	assert(dynamic_sso_string_is_valid(s));

	if (s->capacity <= DYNAMIC_SSO_STRING_ARRAY_SIZE) {
		return (char*)(s->data.array);
	}

	return s->data.allocated_ptr;
}


static inline struct string_view dynamic_sso_string_as_string_view(const struct dynamic_sso_string* const s) {
	if (dynamic_sso_string_is_invalid(s)) {
		return STRING_VIEW_INVALID;
	}

	return (struct string_view){
		.length = s->size,
		.data = dynamic_sso_string_data_ptr(s),
	};
}


static inline bool dynamic_sso_string_is_empty(const struct dynamic_sso_string* const s) {
	assert(dynamic_sso_string_is_valid(s));

	return (s->size == 0);
}

static inline bool dynamic_sso_string_is_not_empty(const struct dynamic_sso_string* const s) {
	assert(dynamic_sso_string_is_valid(s));

	return !(dynamic_sso_string_is_empty(s));
}

static inline char dynamic_sso_string_at(const struct dynamic_sso_string* const s, const size_t index) {
	assert(dynamic_sso_string_is_valid(s));
	assert((s->size > 0) && (index < s->size));

	return dynamic_sso_string_data_ptr(s)[index];
}

static inline size_t dynamic_sso_string_find_first_index_of_char(const struct dynamic_sso_string* const s,
                                                                 const char ch) {
	assert(dynamic_sso_string_is_valid(s));

	return string_view_find_first_index_of_char(dynamic_sso_string_as_string_view(s), ch);
}

static inline bool dynamic_sso_string_contains_char(const struct dynamic_sso_string* const s, const char ch) {
	assert(dynamic_sso_string_is_valid(s));

	return string_view_contains_char(dynamic_sso_string_as_string_view(s), ch);
}


static inline ret_status_t dynamic_sso_string_reserve(struct dynamic_sso_string* const s,
                                                      const size_t required_capacity) {
	assert(dynamic_sso_string_is_valid(s));

	if ((s->capacity >= required_capacity) || (required_capacity <= DYNAMIC_SSO_STRING_ARRAY_SIZE)) {
		return RET_STATUS_SUCCESS;
	}

	size_t new_capacity = s->capacity;

	do {
		new_capacity = (size_t)((double)new_capacity * DYNAMIC_SSO_STRING_GROWTH_FACTOR);
	} while (new_capacity < required_capacity);

	char* new_allocated_data_ptr;
	if (s->capacity <= DYNAMIC_SSO_STRING_ARRAY_SIZE) {
		new_allocated_data_ptr = malloc(sizeof (char) * new_capacity);

		if (new_allocated_data_ptr == NULL) {
			return RET_STATUS_FAILURE;
		}

		memcpy(new_allocated_data_ptr, s->data.array, s->size);
	} else {
		new_allocated_data_ptr = realloc(s->data.allocated_ptr, sizeof (char) * new_capacity);

		if (new_allocated_data_ptr == NULL) {
			return RET_STATUS_FAILURE;
		}
	}

	s->capacity = new_capacity;
	s->data.allocated_ptr = new_allocated_data_ptr;

	return RET_STATUS_SUCCESS;
}

static inline ret_status_t dynamic_sso_string_append_char(struct dynamic_sso_string* const s, const char ch) {
	assert(dynamic_sso_string_is_valid(s));

	if (dynamic_sso_string_reserve(s, (s->size + 1)) != RET_STATUS_SUCCESS) {
		return RET_STATUS_FAILURE;
	}

	char* const data_ptr = dynamic_sso_string_data_ptr(s);

	data_ptr[s->size] = ch;
	++(s->size);

	return RET_STATUS_SUCCESS;
}

static inline ret_status_t dynamic_sso_string_append_buf(struct dynamic_sso_string* const s,
                                                         const char* const buf,
                                                         const size_t buf_size) {
	assert(dynamic_sso_string_is_valid(s));

	if (dynamic_sso_string_reserve(s, (s->size + buf_size)) != RET_STATUS_SUCCESS) {
		return RET_STATUS_FAILURE;
	}

	char* const data_ptr = dynamic_sso_string_data_ptr(s);

	memcpy((data_ptr + s->size), buf, buf_size);
	s->size += buf_size;

	return RET_STATUS_SUCCESS;
}

static inline void dynamic_sso_string_cut(struct dynamic_sso_string* const s, const size_t index, size_t count) {
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

	char* const data = dynamic_sso_string_data_ptr(s);

	memmove((data + index), (data + index + count), (s->size - index - count));
	s->size -= count;
}

static inline void dynamic_sso_string_reverse(struct dynamic_sso_string* const s) {
	assert(dynamic_sso_string_is_valid(s));

	const size_t half_size = (s->size / 2);
	char* const data = dynamic_sso_string_data_ptr(s);

	for (size_t i = 0; i < half_size; ++i) {
		const char ch = data[i];

		const size_t j = (s->size - 1 - i);
		data[i] = data[j];
		data[j] = ch;
	}
}

#endif /* AOC_YEAR2022_DAY05_UTILS_DYNAMIC_SSO_STRING_H */
