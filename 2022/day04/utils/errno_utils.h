/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#ifndef YEAR2022_DAY04_UTILS_ERRNO_UTILS_H
#define YEAR2022_DAY04_UTILS_ERRNO_UTILS_H

#define errno_push()  do { \
	                      int aoc_year2022_day04_internal_pushed_errno_tmp; \
	                      ((void)(aoc_year2022_day04_internal_pushed_errno_tmp = errno))
#define errno_pop()   \
	                      (void)(errno = aoc_year2022_day04_internal_pushed_errno_tmp); \
                      } while(0)

#endif /* YEAR2022_DAY04_UTILS_ERRNO_UTILS_H */
