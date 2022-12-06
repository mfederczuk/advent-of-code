/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef YEAR2022_DAY03_COMMON_H
#define YEAR2022_DAY03_COMMON_H

#include <stddef.h>

typedef size_t prio_t;

static inline prio_t get_item_type_priority(const char item_type) {
	if ((item_type >= 'a') && (item_type <= 'z')) {
		return (prio_t)((item_type - 'a') + 1);
	}

	return (prio_t)((item_type - 'A') + 27);
}


#endif /* YEAR2022_DAY03_COMMON_H */
