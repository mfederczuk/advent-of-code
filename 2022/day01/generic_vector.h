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

#define YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_CONCAT_UNDERLINE(a, b)  a ## _ ## b
#define YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_CONCAT_UNDERLINE_EVALUATED(a, b) \
	YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_CONCAT_UNDERLINE(a, b)

#define YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_FULL_NAME \
	YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_CONCAT_UNDERLINE_EVALUATED(vector, GENERIC_VECTOR_NAME)

#define YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_FULL_NAME_APPEND(x) \
	YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_CONCAT_UNDERLINE_EVALUATED( \
		YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_FULL_NAME, \
		x \
	)

#include <stddef.h>
#include <stdlib.h>

enum {
	        GENERIC_VECTOR_INIT_CAP = 16,
	#define GENERIC_VECTOR_GROWTH_FACTOR 1.5
};

struct YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_FULL_NAME {
	size_t capacity;
	size_t size;
	GENERIC_VECTOR_ELEMENT_TYPE* data;
};

static inline int YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_FULL_NAME_APPEND(init_empty)(
	struct YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_FULL_NAME* const vec
) {
	GENERIC_VECTOR_ELEMENT_TYPE* const data = malloc(sizeof (GENERIC_VECTOR_ELEMENT_TYPE) * GENERIC_VECTOR_INIT_CAP);

	if (data == NULL) {
		return 1;
	}

	*vec = (struct YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_FULL_NAME){
		.capacity = GENERIC_VECTOR_INIT_CAP,
		.size = 0,
		.data = data,
	};

	return 0;
}

static inline void YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_FULL_NAME_APPEND(destroy)(
	struct YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_FULL_NAME* const vec
) {
	free(vec->data);
}

static inline int YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_FULL_NAME_APPEND(reserve)(
	struct YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_FULL_NAME* const vec,
	const size_t required_capacity
) {
	if (vec->capacity >= required_capacity) {
		return 0;
	}

	size_t new_capacity = vec->capacity;

	do {
		new_capacity *= LARGE_STRING_GROWTH_FACTOR;
	} while (new_capacity < required_capacity);

	GENERIC_VECTOR_ELEMENT_TYPE* const new_data =
		realloc(vec->data, sizeof (GENERIC_VECTOR_ELEMENT_TYPE) * new_capacity);

	if (new_data == NULL) {
		return 1;
	}

	vec->capacity = new_capacity;
	vec->data = new_data;

	return 0;
}

static inline int YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_FULL_NAME_APPEND(append)(
	struct YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_FULL_NAME* const vec,
	GENERIC_VECTOR_ELEMENT_TYPE element
) {
	if (YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_FULL_NAME_APPEND(reserve)(vec, (vec->size + 1)) != 0) {
		return 1;
	}

	vec->data[vec->size] = element;
	++(vec->size);

	return 0;
}

static inline GENERIC_VECTOR_ELEMENT_TYPE* YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_FULL_NAME_APPEND(last)(
	struct YEAR2022_DAY01_GENERIC_VECTOR_INTERNAL_FULL_NAME* const vec
) {
	return (vec->data + (vec->size - 1));
}
