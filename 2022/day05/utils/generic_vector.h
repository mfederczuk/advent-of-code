/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef GENERIC_VECTOR_ELEMENT_TYPE
	#error GENERIC_VECTOR_ELEMENT_TYPE needs to be defined
#endif

#ifndef GENERIC_VECTOR_NAME
	#error GENERIC_VECTOR_NAME needs to be defined
#endif


#define AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_CONCAT_UNDERLINE(a, b)  a ## _ ## b
#define AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_CONCAT_UNDERLINE_EVALUATED(a, b) \
	AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_CONCAT_UNDERLINE(a, b)

#define AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_FULL_NAME \
	AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_CONCAT_UNDERLINE_EVALUATED(vector, GENERIC_VECTOR_NAME)

#define AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_FULL_NAME_APPEND(x) \
	AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_CONCAT_UNDERLINE_EVALUATED( \
		AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_FULL_NAME, \
		x \
	)


#include "support_types.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

enum {
	GENERIC_VECTOR_INIT_CAP = 64,
};
#define GENERIC_VECTOR_GROWTH_FACTOR  2

struct AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_FULL_NAME {
	size_t capacity;
	size_t size;
	GENERIC_VECTOR_ELEMENT_TYPE* data;
};


static inline ret_status_t AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_FULL_NAME_APPEND(init_empty)(
	struct AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_FULL_NAME* const vec
) {
	GENERIC_VECTOR_ELEMENT_TYPE* const data = malloc(sizeof (GENERIC_VECTOR_ELEMENT_TYPE) * GENERIC_VECTOR_INIT_CAP);

	if (data == NULL) {
		return RET_STATUS_FAILURE;
	}

	*vec = (struct AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_FULL_NAME){
		.capacity = GENERIC_VECTOR_INIT_CAP,
		.size = 0,
		.data = data,
	};

	return RET_STATUS_SUCCESS;
}

static inline void AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_FULL_NAME_APPEND(destroy)(
	struct AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_FULL_NAME* const vec
) {
	free(vec->data);
}


static inline ret_status_t AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_FULL_NAME_APPEND(reserve)(
	struct AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_FULL_NAME* const vec,
	const size_t required_capacity
) {
	if (vec->capacity >= required_capacity) {
		return RET_STATUS_SUCCESS;
	}

	size_t new_capacity = vec->capacity;

	do {
		new_capacity = (size_t)((double)new_capacity * GENERIC_VECTOR_GROWTH_FACTOR);
	} while (new_capacity < required_capacity);

	GENERIC_VECTOR_ELEMENT_TYPE* const new_data =
		realloc(
			vec->data,
			(sizeof (GENERIC_VECTOR_ELEMENT_TYPE) * new_capacity)
		);

	if (new_data == NULL) {
		return RET_STATUS_FAILURE;
	}

	vec->capacity = new_capacity;
	vec->data = new_data;

	return RET_STATUS_SUCCESS;
}

static inline int AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_FULL_NAME_APPEND(append)(
	struct AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_FULL_NAME* const vec,
	GENERIC_VECTOR_ELEMENT_TYPE element
) {
	const ret_status_t ret =
		AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_FULL_NAME_APPEND(reserve)(
			vec,
			(vec->size + 1)
		);

	if (ret != RET_STATUS_SUCCESS) {
		return RET_STATUS_FAILURE;
	}

	vec->data[vec->size] = element;
	++(vec->size);

	return RET_STATUS_SUCCESS;
}


static inline GENERIC_VECTOR_ELEMENT_TYPE* AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_FULL_NAME_APPEND(last)(
	struct AOC_YEAR2022_DAY05_GENERIC_VECTOR_INTERNAL_FULL_NAME* const vec
) {
	assert(vec->size > 0);
	return (vec->data + (vec->size - 1));
}
