/*
 * Copyright (c) 2022 Michael Federczuk
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include "common.h"
#include "dynamic_sso_string.h"
#include "file_line_iter.h"
#include "string_view_io.h"
#include "string_view.h"
#include <stdbool.h>
#include <stdio.h>

struct elf_group {
	struct dynamic_sso_string elf_backpacks[3];
};

static inline struct elf_group elf_group_create_with_backpack_1(const struct dynamic_sso_string backpack_1) {
	return (struct elf_group){
		.elf_backpacks[0] = backpack_1,
		.elf_backpacks[1] = DYNAMIC_SSO_STRING_INVALID,
		.elf_backpacks[2] = DYNAMIC_SSO_STRING_INVALID,
	};
}

#define ELF_GROUP_INVALID  elf_group_create_with_backpack_1(DYNAMIC_SSO_STRING_INVALID)

#define GENERIC_VECTOR_ELEMENT_TYPE  struct elf_group
#define GENERIC_VECTOR_NAME  elf_group
#include "generic_vector.h"
#undef GENERIC_VECTOR_NAME
#undef GENERIC_VECTOR_ELEMENT_TYPE

#define array_size(arr)  (sizeof (arr) / sizeof (*(arr)))

int main(const int argc, const char* const* argv) {
	if (argc < 2) {
		fprintf(stderr, "%s: missing argument: <input_file>\n", argv[0]);
		return 3;
	}

	struct vector_elf_group elf_groups;
	if (vector_elf_group_init_empty(&elf_groups) != 0) {
		perror("vector_elf_group_init_empty");
		return EXIT_FAILURE;
	}

	if (vector_elf_group_append(&elf_groups, ELF_GROUP_INVALID) != 0) {
		perror("vector_elf_group_append");
		vector_elf_group_destroy(&elf_groups);
		return EXIT_FAILURE;
	}

	struct file_line_iter iter;
	if (file_line_iter_init(&iter, argv[1]) != 0) {
		perror("file_line_iter_init");
		vector_elf_group_destroy(&elf_groups);
		return EXIT_FAILURE;
	}

	struct file_line_iter_next next_line;
	do {
		if (file_line_iter_next(&iter, &next_line) != 0) {
			file_line_iter_destroy(&iter);
			return EXIT_FAILURE;
		}

		if (!(next_line.valid)) {
			break;
		}

		struct elf_group* const current_elf_group = vector_elf_group_last(&elf_groups);

		bool set = false;

		for (size_t i = 0; i < array_size(current_elf_group->elf_backpacks); ++i) {
			if (dynamic_sso_string_is_invalid(&(current_elf_group->elf_backpacks[i]))) {
				current_elf_group->elf_backpacks[i] = next_line.line;
				set = true;
				break;
			}
		}

		if (!set) {
			vector_elf_group_append(&elf_groups, elf_group_create_with_backpack_1(next_line.line));
		}
	} while (1);

	file_line_iter_destroy(&iter);

	prio_t prio_sum = 0;

	for (size_t i = 0; i < elf_groups.size; ++i) {
		struct dynamic_sso_string elf_backpacks_1 = elf_groups.data[i].elf_backpacks[0];
		struct dynamic_sso_string elf_backpacks_2 = elf_groups.data[i].elf_backpacks[1];
		struct dynamic_sso_string elf_backpacks_3 = elf_groups.data[i].elf_backpacks[2];

		for (size_t i = 0; i < elf_backpacks_1.size; ++i) {
			const char item_type = dynamic_sso_string_at(&elf_backpacks_1, i);
			const bool in_backpack_2 = dynamic_sso_string_contains_char(&elf_backpacks_2, item_type, 0, (size_t)-1);
			const bool in_backpack_3 = dynamic_sso_string_contains_char(&elf_backpacks_3, item_type, 0, (size_t)-1);

			if (in_backpack_2 && in_backpack_3) {
				prio_sum += get_item_type_priority(item_type);
				break;
			}
		}

		dynamic_sso_string_destroy(&elf_backpacks_3);
		dynamic_sso_string_destroy(&elf_backpacks_2);
		dynamic_sso_string_destroy(&elf_backpacks_1);
	}

	vector_elf_group_destroy(&elf_groups);

	printf("%zu\n", prio_sum);

	return 0;
}
