/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef AOC_YEAR2022_DAY05_UTILS_ERRNO_UTILS_H
#define AOC_YEAR2022_DAY05_UTILS_ERRNO_UTILS_H

#define errno_push()  do { \
	                      int aoc_year2022_day05_internal_pushed_errno_tmp; \
	                      ((void)(aoc_year2022_day05_internal_pushed_errno_tmp = errno))
#define errno_pop()   \
	                      (void)(errno = aoc_year2022_day05_internal_pushed_errno_tmp); \
                      } while (0)

#endif /* AOC_YEAR2022_DAY05_UTILS_ERRNO_UTILS_H */
