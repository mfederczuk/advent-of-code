/*
 * SPDX-License-Identifier: CC0-1.0
 */

#ifndef AOC_YEAR2022_DAY05_VECTOR_DYNAMIC_SSO_STRING_H
#define AOC_YEAR2022_DAY05_VECTOR_DYNAMIC_SSO_STRING_H

#include "utils/dynamic_sso_string.h"

#define GENERIC_VECTOR_ELEMENT_TYPE struct dynamic_sso_string
#define GENERIC_VECTOR_NAME dynamic_sso_string
#include "utils/generic_vector.h"
#undef GENERIC_VECTOR_NAME
#undef GENERIC_VECTOR_ELEMENT_TYPE

#endif /* AOC_YEAR2022_DAY05_VECTOR_DYNAMIC_SSO_STRING_H */
