/*
 * Copyright (c) 2020 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	char* input_file = "example_input";
	if(argc >= 2) input_file = argv[1];

	FILE* f = fopen(input_file, "r");
	char buf[10]; // 10 = (7 chars of front/back) + (3 chars of left/right)

	size_t i;
	short int min_row, max_row,
	          min_col, max_col;

	bool ids[128 * 8];
	memset(ids, false, sizeof(ids));

	while(fread(buf, sizeof(*buf), (sizeof(buf) / sizeof(*buf)), f) == (sizeof(buf) / sizeof(*buf))) {
		min_row = 0;
		max_row = 127;
		for(i = 0; i < 7; ++i) {
			switch(buf[i]) {
				case('F'): {
					max_row -= (max_row - (min_row - 1)) / 2;
					break;
				}
				case('B'): {
					min_row += (max_row - (min_row - 1)) / 2;
				}
			}
		}

		min_col = 0;
		max_col = 7;
		for(; i < 10; ++i) {
			switch(buf[i]) {
				case('L'): {
					max_col -= (max_col - (min_col - 1)) / 2;
					break;
				}
				case('R'): {
					min_col += (max_col - (min_col - 1)) / 2;
				}
			}
		}

		ids[min_row * 8 + min_col] = true;

		fgetc(f); // skip newline
	}

	fclose(f);

	i = 0;

	// skip the first few rows that don't exist
	for(; i < (sizeof(ids) / sizeof(*ids)) && !ids[i]; ++i);

	// search for our seat
	for(; i < (sizeof(ids) / sizeof(*ids)) && ids[i]; ++i);

	printf("%zd\n", i);

	return 0;
}
