/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef YEAR2022_DAY03_STRING_VIEW_IO_H
#define YEAR2022_DAY03_STRING_VIEW_IO_H

#include "string_view.h"
#include <stdio.h>

static inline size_t fwrite_string_view(const struct string_view sv, FILE* stream) {
	return fwrite(sv.begin, sizeof *(sv.begin), string_view_length(sv), stream);
}

#endif /* YEAR2022_DAY03_STRING_VIEW_IO_H */
