/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef YEAR2022_DAY01_LARGE_STRING_ITER_H
#define YEAR2022_DAY01_LARGE_STRING_ITER_H

#include "large_string.h"
#include "string_view.h"
#include <stdbool.h>

struct large_string_line_iter {
	struct large_string* s;
	size_t current_index;
};

static inline struct large_string_line_iter large_string_line_iter_create(struct large_string* const s) {
	return (struct large_string_line_iter){
		.s = s,
		.current_index = 0,
	};
}

/**
 * The returned string view will not contain the newline character.
 */
static inline struct string_view large_string_line_iter_next(struct large_string_line_iter* const iter) {
	if ((iter->current_index >= iter->s->size) ||
	    (iter->s->size == 0)) {

		return STRING_VIEW_INVALID;
	}

	const size_t next_nl_ch_index =
		large_string_find_first_index_of_char(
			iter->s,
			'\n',
			iter->current_index,
			iter->s->size
		);

	const struct string_view sv = {
		.begin = (iter->s->data + iter->current_index),
		.end   = (iter->s->data + next_nl_ch_index),
	};

	iter->current_index = next_nl_ch_index;
	if (next_nl_ch_index < iter->s->size) {
		++(iter->current_index);
	}

	return sv;
}

#endif /* YEAR2022_DAY01_LARGE_STRING_ITER_H */
