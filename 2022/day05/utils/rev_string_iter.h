/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_YEAR2022_DAY05_UTILS_REV_STRING_ITER_H
#define AOC_YEAR2022_DAY05_UTILS_REV_STRING_ITER_H

#include <stddef.h>

struct rev_string_iter {
	char* data;
	size_t cur_index;
};

static inline struct rev_string_iter rev_string_iter_create(char* const data, const size_t length) {
	return (struct rev_string_iter){
		.data = data,
		.cur_index = length,
	};
}

static inline char* rev_string_iter_next(struct rev_string_iter* const iter) {
	if (iter->cur_index == 0) {
		return NULL;
	}

	--(iter->cur_index);
	return (iter->data + iter->cur_index);
}

#endif /* AOC_YEAR2022_DAY05_UTILS_REV_STRING_ITER_H */
